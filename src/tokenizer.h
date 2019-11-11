#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum{
    TK_PTR, TK_VAL, TK_IO, TK_LP, TK_EOF
} token_type;

typedef struct token{
    token_type type;
    int val;
    struct token *next;
} token;

token *token_add(token *back, token_type t, int v);
void token_free(token *front);
token *tokenize(string *s);

#endif