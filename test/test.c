#include <stdio.h>
#include <assert.h>
#include "../src/containers.h"
#include "../src/tokenizer.h"

int main(){
    string *s = string_init();
    char src[] = "++--<><>,.asdpo2ほあ\nｓ<>/+[as<>/.}]";
    for(size_t i=0;src[i]!=0;++i) string_push(s, src[i]);
    token *tk = tokenize(s), *cur = tk;

    token_type chk_type[] = {
        TK_VAL, TK_VAL, TK_VAL, TK_VAL, TK_PTR, TK_PTR, TK_PTR, TK_PTR, TK_IO , TK_IO ,
        TK_PTR, TK_PTR, TK_VAL, TK_LP , TK_PTR, TK_PTR, TK_IO , TK_LP , TK_EOF
    };
    int chk_val[] = {
        1, 1, -1, -1, -1, 1, -1, 1, 1, 0, -1, 1, 1, 0, -1, 1, 0, 1, 0
    };
    for(size_t i=0;i<sizeof(chk_type)/sizeof(*chk_type);++i){
        assert(cur != NULL);
        assert(cur->type == chk_type[i]);
        assert(cur->val == chk_val[i]);
        cur = cur->next;
    }

    string_free(s);
    token_free(tk);

    return 0;
}