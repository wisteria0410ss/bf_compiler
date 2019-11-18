#include <stdlib.h>
#include "containers.h"
#include "tokenizer.h"
#include "util.h"

string *tokenize(string *s){
    const char tokens[] = "<>+-.,[]";
    string *tk = string_init();

    for(char *c=s->buf;*c;++c){
        for(int i=0;i<8;++i){
            if(*c == tokens[i]){
                string_push(tk, *c); 
                break;
            }
        }
    }
    return tk;
}