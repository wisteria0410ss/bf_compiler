#include <stddef.h>

typedef struct{
    char *buf;
    size_t len, cnt;
} string;
string *string_init();
void string_push(string *s, char c);
void string_free(string *s);