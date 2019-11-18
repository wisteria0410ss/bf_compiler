#include <stdio.h>
#include "parser.h"

void asm_loop(FILE *fp, code_tree *pos);

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
                fprintf(fp, "\tinc  dword ptr [rbx]\n");
                break;
            case '-':
                fprintf(fp, "\tdec  dword ptr [rbx]\n");
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
                        "\tcmp  dword ptr [rbx], 0\n"
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