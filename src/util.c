#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void error(int err_type){
    switch(err_type){
    case ERR_ALLOC:
        fprintf(stderr, "failed to allocate memory.\n");
        break;
    case ERR_LBEGIN:
        fprintf(stderr, "too many \'[\'s.\n");
        break;
    case ERR_LEND:
        fprintf(stderr, "too many \']\'s.\n");
        break;
    case ERR_FOPEN:
        fprintf(stderr, "failed to open file.\n");
        break;
    case ERR_ARGS:
        fprintf(stderr, "usage:\n\tbfc [-S] [-o outfile] infile\n");
        break;
    case ERR_CHMOD:
        fprintf(stderr, "failed to make the output file executable.\n");
        break;
    default:
        fprintf(stderr, "unknown error\n");
        break;
    }
    exit(1);
}