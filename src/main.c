#include <stdio.h>
#include "containers.h"
#include "tokenizer.h"
#include "parser.h"
#include "generator.h"
#include "util.h"

int main(){
    string *source, *tokens;
    code_tree *tree;
    FILE *fp_in, *fp_out, *fp_bin;
    char c;

    source = string_init();

    fp_in = stdin;
    while((c = fgetc(fp_in)) != EOF) string_push(source, c);
    tokens = tokenize(source);
    tree = parse(tokens);
    
    fp_out = stdout;
    generate_asm(fp_out, tree);

    fp_bin = fopen("a.out", "wb");
    if(fp_bin == NULL) error(ERR_FOPEN);
    generate_elf(fp_bin, tree);
    fclose(fp_bin);
    
    return 0;
}