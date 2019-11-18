#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include "containers.h"

typedef struct code_tree{
    char token_type;
    int value;
    size_t code_length;
    struct code_tree *next;
    struct code_tree *child;
} code_tree;

code_tree *node_new(code_tree *prev, char type);
code_tree *node_begin();
code_tree *parse(string *tokens);

#endif