#include <stdio.h>
#include "containers.h"
#include "tokenizer.h"
#include "parser.h"
#include "generator.h"

int main(){
    string *source, *tokens;
    code_tree *tree;
    FILE *fp_in, *fp_out;
    char c;

    source = string_init();

    fp_in = stdin;
    while((c = fgetc(fp_in)) != EOF) string_push(source, c);
    tokens = tokenize(source);
    tree = parse(tokens);
    
    fp_out = stdout;
    generate_asm(fp_out, tree);    
    
    return 0;
}