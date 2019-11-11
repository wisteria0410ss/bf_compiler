#include <stdio.h>
#include "containers.h"

int main(){
    string *s = string_init();
    char c;

    while((c = fgetc(stdin)) != EOF) string_push(s, c);
    printf("%s", s->buf);
    string_free(s);
    
    return 0;
}