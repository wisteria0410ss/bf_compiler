#include <stdio.h>
#include <stdlib.h>
#include "containers.h"
#include "tokenizer.h"
#include "parser.h"
#include "generator.h"
#include "util.h"

int main(int argc, char **argv){
    string *fn_input, *fn_output;
    fn_input = string_init();
    fn_output = string_init();

    int pos = 1;
    int output_asm = 0;
    while(pos < argc){
        if(argv[pos][0] == '-'){
            switch(argv[pos][1]){
            case 'S':
                output_asm = 1;
                ++pos;
                break;
            case 'o':
                ++pos;
                if(pos >= argc || fn_output->cnt > 0) error(ERR_ARGS);
                for(int i=0;argv[pos][i];++i) string_push(fn_output, argv[pos][i]);
                ++pos;
                break;
            default:
                error(ERR_ARGS);
                break;
            }
        }else{
            if(fn_input->cnt > 0) error(ERR_ARGS);
            for(int i=0;argv[pos][i];++i) string_push(fn_input, argv[pos][i]);
            ++pos;
        }
    }
    
    string *source, *tokens;
    code_tree *tree;
    FILE *fp_in, *fp_out;
    char c;

    if(fn_input->cnt == 0) fp_in = stdin;
    else{
        fp_in = fopen(fn_input->buf, "r");
        if(fp_in == NULL) error(ERR_FOPEN);
    }
    
    source = string_init();
    while((c = fgetc(fp_in)) != EOF) string_push(source, c);
    
    if(fp_in != stdin) fclose(fp_in);

    tokens = tokenize(source);
    tree = parse(tokens);
    
    if(fn_output->cnt == 0){
        if(output_asm) fp_out = stdout;
        else{
            fp_out = fopen("a.out", "wb");
            for(int i=0;"a.out"[i];++i) string_push(fn_output, "a.out"[i]);
        }
        if(fp_out == NULL) error(ERR_FOPEN);
    }
    else{
        fp_out = fopen(fn_output->buf, output_asm?"w":"wb");
        if(fp_out == NULL) error(ERR_FOPEN);
    }

    if(output_asm) generate_asm(fp_out, tree);
    else{
        generate_elf(fp_out, tree);
        if(fp_out != stdout){
            string *comm_str = string_init();
            char comm[] = "chmod +x ";
            for(size_t i=0;comm[i];++i) string_push(comm_str, comm[i]);
            for(size_t i=0;i<fn_output->cnt;++i) string_push(comm_str, fn_output->buf[i]);
            int info = system(comm_str->buf);
            if(info != 0) error(ERR_CHMOD);
        }
    }

    if(fp_out != stdout) fclose(fp_out);
    
    return 0;
}