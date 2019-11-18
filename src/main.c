#include <stdio.h>
#include "containers.h"
#include "tokenizer.h"

int main(){
    string *source, *tokens;
    char c;

    source = string_init();

    while((c = fgetc(stdin)) != EOF) string_push(source, c);
    tokens = tokenize(source);

    printf("%s\n", tokens->buf);

    string_free(source);
    string_free(tokens);
    
    return 0;
}