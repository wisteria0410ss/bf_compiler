#include <stdlib.h>
#include "containers.h"
#include "tokenizer.h"
#include "util.h"

token *token_add(token *back, token_type t, int v){
    token *tk = malloc(sizeof(tk));
    if(tk == NULL) error(ERR_ALLOC);
    if(back != NULL) back->next = tk;
    tk->type = t;
    tk->val = v;
    tk->next = NULL;
    return tk;
}

void token_free(token *front){
    while(front){
        token *next = front->next;
        free(front);
        front = next;
    }
}

token *tokenize(string *s){
    token *cur = NULL, *token_front = NULL;
    for(char *c=s->buf;;++c){
        if(*c == '>')       cur = token_add(cur, TK_PTR, +1);
        else if(*c == '<')  cur = token_add(cur, TK_PTR, -1);
        else if(*c == '+')  cur = token_add(cur, TK_VAL, +1);
        else if(*c == '-')  cur = token_add(cur, TK_VAL, -1);
        else if(*c == '.')  cur = token_add(cur, TK_IO ,  0);
        else if(*c == ',')  cur = token_add(cur, TK_IO ,  1);
        else if(*c == '[')  cur = token_add(cur, TK_LP ,  0);
        else if(*c == ']')  cur = token_add(cur, TK_LP ,  1);
        else if(*c == 0){
            cur = token_add(cur, TK_EOF, 0);
            break;
        }
        if(token_front == NULL) token_front = cur;
    }
    return token_front;
}