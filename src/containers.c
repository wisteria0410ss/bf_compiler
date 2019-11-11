#include <stdlib.h>
#include "containers.h"

string *string_init(){
    string *s = (string*)malloc(sizeof(string));
    s->buf = (char*)malloc(sizeof(char)*16);
    s->buf[0] = 0;
    s->len = 16;
    s->cnt = 0;

    return s;
}

void string_push(string *s, char c){
    if(s->cnt + 1 >= s->len){
        s->len *= 2;
        s->buf = (char*)realloc(s->buf, s->len);
    }
    s->buf[s->cnt++] = c;
    s->buf[s->cnt] = 0;
}

void string_free(string *s){
    free(s);
}