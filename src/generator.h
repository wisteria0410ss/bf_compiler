#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "parser.h"

void generate_asm(FILE *fp, code_tree *tree);
void generate_elf(FILE *fp, code_tree *tree);

#endif