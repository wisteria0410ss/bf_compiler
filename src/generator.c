#include <stdio.h>
#include <elf.h>
#include "parser.h"

void asm_loop(FILE *fp, code_tree *pos);
void elf_loop(code *c, code_tree *pos);
void elf_output(FILE* fp, code* c);

static intptr_t pos_read, pos_write;

void generate_asm(FILE *fp, code_tree *tree){
    fprintf(fp, 
        ".intel_syntax noprefix\n"
        ".global _start\n"
        "\n"
        ".data\n"
        "buf:\n"
            "\t.zero 65536\n"
        "\n"
        ".text\n"
        "read:\n"
            "\tlea  rsi, [rbx]\n"
            "\txor  rax, rax\n"
            "\tmov  rdi, 1\n"
            "\tmov  rdx, rdi\n"
            "\tsyscall\n"
            "\tretq\n"
        "write:\n"
            "\tlea  rsi, [rbx]\n"
            "\tmov  rdx, 1\n"
            "\tmov  rax, rdx\n"
            "\tmov  rdi, rdx\n"
            "\tsyscall\n"
            "\tretq\n"
        "_start:\n"
            "\tlea  rbx, [buf]\n");
    
    asm_loop(fp, tree);

    fprintf(fp, 
            "\tmov  rax, 0x3c\n"
            "\txor  rdi, rdi\n"
            "\tsyscall\n"
        );
}

void asm_loop(FILE *fp, code_tree *pos){
    while(pos){
        switch(pos->token_type){
            case '>':
                fprintf(fp, "\tinc  rbx\n");
                break;
            case '<':
                fprintf(fp, "\tdec  rbx\n");
                break;
            case '+':
                fprintf(fp, "\tinc  byte ptr [rbx]\n");
                break;
            case '-':
                fprintf(fp, "\tdec  byte ptr [rbx]\n");
                break;
            case ',':
                fprintf(fp, "\tcall read\n");
                break;
            case '.':
                fprintf(fp, "\tcall write\n");
                break;
            case '[':
                fprintf(fp,
                    ".L%d:\n"
                        "\tcmp  byte ptr [rbx], 0\n"
                        "\tje   .L%d_END\n",
                    pos->value, pos->value);
                asm_loop(fp, pos->child);
                fprintf(fp,
                        "\tjmp  .L%d\n"
                    ".L%d_END:\n",
                    pos->value, pos->value);
                break;
        }
        pos = pos->next;
    }
}

void generate_elf(FILE *fp, code_tree *tree){
    code *c;

    c = code_init();
    
    pos_read = code_position(c);
        code_push(c, 19,
        0x48, 0x8d, 0x33,                           // lea  rsi, [rbx]
        0x48, 0x31, 0xc0,                           // xor  rax, rax
        0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00,   // mov  rdi, 1
        0x48, 0x89, 0xfa,                           // mov  rdx, rdi
        0x0f, 0x05,                                 // syscall
        0xc3                                        // retq
    );
    pos_write = code_position(c);
    code_push(c, 19,
        0x48, 0x8d, 0x33,                           // lea  rsi, [rbx]
        0x48, 0xc7, 0xc2, 0x01, 0x00, 0x00, 0x00,   // mov  rdx, 1
        0x48, 0x89, 0xd0,                           // mov  rax, rdx
        0x48, 0x89, 0xd7,                           // mov  rdi, rdx
        0x0f, 0x05,                                 // syscall
        0xc3                                        // retq
    );
    c->entry = code_position(c);

    union{
        intptr_t p;
        unsigned char b[4];
    } p_data;

    p_data.p = (
        0x00401000 +        // position of .text
        19 + 19 + 7 +       // read, write, "lea rbx, [buf]"
        tree->code_length + // code's size
        16 +                // exit
    0xfff) / 0x1000 * 0x1000;

    code_push(c, 7, 0x48, 0xc7, 0xc3,               // mov  rbx, [buf]
        p_data.b[0], p_data.b[1], p_data.b[2], p_data.b[3]);

    elf_loop(c, tree);

    code_push(c, 16,
        0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00,   // mov  rax, 0x3c
        0x48, 0xc7, 0xc7, 0x00, 0x00, 0x00, 0x00,   // mov  rdi, 0x00
        0x0f, 0x05                                  // syscall
    );

    elf_output(fp, c);
}

void elf_loop(code *c, code_tree *pos){
    union{
        ptrdiff_t d;
        unsigned char b[4];
    } rel;

    while(pos){
        switch(pos->token_type){
            case '>':
                code_push(c, 3, 0x48, 0xff, 0xc3);  // inc  rbx
                break;
            case '<':
                code_push(c, 3, 0x48, 0xff, 0xcb);  // dec  rbx
                break;
            case '+':
                code_push(c, 2, 0xfe, 0x03);        // inc  byte ptr [rbx]
                break;
            case '-':
                code_push(c, 2, 0xfe, 0x0b);        // dec  byte ptr [rbx]
                break;
            case ',':
                rel.d = pos_read;
                rel.d -= code_position(c) + 5;
                code_push(c, 5, 0xe8, rel.b[0], rel.b[1], rel.b[2], rel.b[3]);
                                                    // call read
                break;
            case '.':
                rel.d = pos_write;
                rel.d -= code_position(c) + 5;
                code_push(c, 5, 0xe8, rel.b[0], rel.b[1], rel.b[2], rel.b[3]);
                                                    // call write
                break;
            case '[':
                                                    // .Lx:
                code_push(c, 3, 0x80, 0x3b, 0x00);
                                                    // cmp  byte ptr [rbx], 0
                rel.d = pos->code_length - 9;
                code_push(c, 6, 0x0f, 0x84, rel.b[0], rel.b[1], rel.b[2], rel.b[3]);
                                                    // je   .Lx_END
                elf_loop(c, pos->child);
                rel.d = -pos->code_length;
                code_push(c, 5, 0xe9, rel.b[0], rel.b[1], rel.b[2], rel.b[3]);
                                                    // jmp  .Lx
                                                    // .Lx_END:
                break;
        }
        pos = pos->next;
    }
}

void elf_output(FILE* fp, code* c){
    /*
        0x00400000  ELF header
                    Program header[0]: header   R
                    Program header[1]: .text    R X
                    Program header[2]: .data    RW
        0x00401000  .text
                        _read
                        _write
                        _start
        0x0040_000  .data
                        buf
                    .shstrtbl
                    Section header[0]: 
                    Section header[1]: .text
                    Section header[2]: .data
                    Section header[3]: .shstrtab
    */
    unsigned char pad[0x10000] = {};
    unsigned char shstrtab[] = 
        "\0"
        ".text\0"
        ".data\0"
        ".shstrtab";

    size_t n_buf = 65536;
    size_t n_phdr = 3;
    size_t n_shdr = 4;
    intptr_t p_ehdr = 0x00400000;
    intptr_t p_phdr = p_ehdr + sizeof(Elf64_Ehdr);
    intptr_t p_text = 0x00401000;
    intptr_t p_data = (p_text + code_position(c) + 0xfff) / 0x1000 * 0x1000;
    intptr_t p_shst = p_data + n_buf;
    intptr_t p_shdr = (p_shst + sizeof(shstrtab) + 0xf) / 0x10 * 0x10;

    Elf64_Ehdr ehdr = {
        {
            ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3,
            ELFCLASS64, ELFDATA2LSB, EV_CURRENT, ELFOSABI_SYSV
        },
        ET_EXEC,
        EM_X86_64,
        EV_CURRENT,
        p_text + c->entry,
        p_phdr - p_ehdr,
        p_shdr - p_ehdr,
        0,
        sizeof(Elf64_Ehdr),
        sizeof(Elf64_Phdr),
        n_phdr,
        sizeof(Elf64_Shdr),
        n_shdr,
        n_shdr - 1
    };
    Elf64_Phdr phdr[] = {
        {
            PT_LOAD,
            PF_R,
            0,
            p_ehdr,
            p_ehdr,
            sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) * n_phdr,
            sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) * n_phdr,
            0x1000
        },
        {
            PT_LOAD,
            PF_R | PF_X,
            p_text - p_ehdr,
            p_text,
            p_text,
            code_position(c),
            code_position(c),
            0x1000
        },
        {
            PT_LOAD,
            PF_R | PF_W,
            p_data - p_ehdr,
            p_data,
            p_data,
            n_buf,
            n_buf,
            0x1000
        }
    };
    Elf64_Shdr shdr[] = {
        {},
        {
            1,
            SHT_PROGBITS,
            SHF_EXECINSTR,
            p_text,
            p_text - p_ehdr,
            code_position(c),
            0,
            0,
            1,
            0
        },
        {
            1 + 6,
            SHT_PROGBITS,
            SHF_WRITE,
            p_data,
            p_data - p_ehdr,
            n_buf,
            0,
            0,
            1,
            0
        },
        {
            1 + 6 + 6,
            SHT_STRTAB,
            0,
            0,
            p_shst - p_ehdr,
            sizeof(shstrtab),
            0,
            0,
            1,
            0
        }
    };

    intptr_t addr = p_ehdr;

    fwrite(&ehdr, sizeof(ehdr), 1, fp);
    addr += sizeof(ehdr);
    fwrite(phdr, sizeof(phdr[0]), sizeof(phdr)/sizeof(phdr[0]), fp);
    addr += sizeof(phdr);
    fwrite(pad, 1, p_text - addr, fp);
    addr = p_text;

    fwrite(c->buf, sizeof(c->buf[0]), code_position(c), fp);
    addr += sizeof(c->buf[0]) * code_position(c);
    fwrite(pad, 1, p_data - addr, fp);
    addr = p_data;

    fwrite(pad, 1, n_buf, fp);
    addr += n_buf;
    fwrite(shstrtab, sizeof(shstrtab[0]), sizeof(shstrtab)/sizeof(shstrtab[0]), fp);
    addr += sizeof(shstrtab);
    fwrite(pad, 1, p_shdr - addr, fp);
    addr = p_shdr;

    fwrite(shdr, sizeof(shdr[0]), sizeof(shdr)/sizeof(shdr[0]), fp);
    addr += sizeof(shdr);
}