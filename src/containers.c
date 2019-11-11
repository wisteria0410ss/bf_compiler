#include <stdlib.h>
#include "containers.h"
#include "util.h"

string *string_init(){
    string *s = malloc(sizeof(*s));
    if(s == NULL) error(ERR_ALLOC);
    s->buf = malloc(sizeof(*s->buf)*16);
    if(s->buf == NULL) error(ERR_ALLOC);
    s->buf[0] = 0;
    s->len = 16;
    s->cnt = 0;

    return s;
}

void string_push(string *s, char c){
    if(s->cnt + 1 >= s->len){
        s->len *= 2;
        s->buf = realloc(s->buf, s->len);
        if(s->buf == NULL) error(ERR_ALLOC);
    }
    s->buf[s->cnt++] = c;
    s->buf[s->cnt] = 0;
}

void string_free(string *s){
    free(s);
}