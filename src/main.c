#include <stdio.h>
#include "containers.h"
#include "tokenizer.h"
#include "parser.h"

int main(){
    string *source, *tokens;
    code_tree *tree;
    char c;

    source = string_init();

    while((c = fgetc(stdin)) != EOF) string_push(source, c);
    tokens = tokenize(source);
    tree = parse(tokens);

    printf("%s\n", tokens->buf);

    string_free(source);
    string_free(tokens);
    
    return 0;
}