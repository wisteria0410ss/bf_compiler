#include <stdlib.h>
#include "parser.h"
#include "containers.h"
#include "util.h"

void program();
size_t loop();

code_tree *node_new(code_tree *prev, char type){
    code_tree *ct = malloc(sizeof(code_tree));
    if(prev != NULL) prev->next = ct;
    ct->token_type = type;
    if(type == '[') ct->code_length = 15;
    else if(type == ',' || type == '.') ct->code_length = 5;
    else ct->code_length = 3;

    return ct;
}

code_tree *node_begin(){
    code_tree *ct = malloc(sizeof(code_tree));
    ct->token_type = 'B';
    ct->code_length = 0;

    return ct;
}

static string *tk;
static size_t pos;
static size_t loop_cnt;

static code_tree *root, *tail;

code_tree *parse(string *tokens){
    tk = tokens;
    root = node_begin();
    tail = root;
    
    loop_cnt = 0;
    program();
    
    return root;
}

void program(){
    while(tk->buf[pos] != 0){
        if(tk->buf[pos] == ']') error(ERR_LEND);
        else if(tk->buf[pos] == '['){
            code_tree *t = node_new(tail, tk->buf[pos]);
            ++pos;
            t->value = loop_cnt++;
            tail = t->child = node_begin();
            t->code_length = 15 + loop();
            tail = t;
        }else{
            tail = node_new(tail, tk->buf[pos]);
            ++pos;
        }
    }
}

size_t loop(){
    size_t len = 0;
    while(tk->buf[pos] != ']'){
        if(tk->buf[pos] == 0) error(ERR_LBEGIN);
        else if(tk->buf[pos] == '['){
            code_tree *t = node_new(tail, tk->buf[pos]);
            ++pos;
            t->value = loop_cnt++;
            tail = t->child = node_begin();
            t->code_length = 15 + loop();
            tail = t;
        }else{
            tail = node_new(tail, tk->buf[pos]);
            ++pos;
        }
        len += tail->code_length;
    }
    ++pos;
    return len;
}