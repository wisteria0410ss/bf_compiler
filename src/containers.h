#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <stddef.h>
#include <stdint.h>

typedef struct{
    char *buf;
    size_t len, cnt;
} string;
string *string_init();
void string_push(string *s, char c);

typedef struct{
    size_t len;
    size_t p;
    intptr_t entry;
    unsigned char *buf;
} code;

code *code_init();
void code_push(code *c, size_t n, ...);
intptr_t code_position(code* c);

#endif