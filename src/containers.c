#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
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

code *code_init(){
    code *c = (code*)malloc(sizeof(code));
    if(c == NULL) error(ERR_ALLOC);

    c->buf = (unsigned char*)malloc(sizeof(unsigned char) * 16);
    if(c->buf == NULL) error(ERR_ALLOC);
    c->len = 16;
    c->p = 0;

    return c;
}
void code_push(code *c, size_t n, ...){
    va_list ap;
    va_start(ap, n);
    for(size_t i=0;i<n;++i){
        if(c->len <= c->p){
            c->buf = (unsigned char*)realloc(c->buf, c->len * 2);
            if(c->buf == NULL) error(ERR_ALLOC);
            c->len *= 2;
        }
        c->buf[c->p] = (unsigned char)va_arg(ap, int);
        ++(c->p);
    }
    va_end(ap);
}
intptr_t code_position(code* c){
    return (intptr_t)c->p;
}
