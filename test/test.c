#include <stdio.h>
#include <assert.h>
#include "../src/containers.h"
#include "../src/tokenizer.h"

int main(){
    string *s = string_init();
    char src[] = "++--<><>,.asdpo2ほあ\nｓ<>/+[as<>/.}]";
    char tok[] = "++--<><>,.<>+[<>.]";
    for(size_t i=0;src[i]!=0;++i) string_push(s, src[i]);
    string *tk = tokenize(s);

    for(size_t i=0;i<sizeof(tok)/sizeof(tok[0]);++i){
        assert(tok[i] == tk->buf[i]);
    }

    string_free(s);
    string_free(tk);

    return 0;
}