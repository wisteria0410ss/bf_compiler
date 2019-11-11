#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void error(int err_type){
    switch(err_type){
    case ERR_ALLOC:
        fprintf(stderr, "failed to allocate memory.\n");
        break;    
    default:
        fprintf(stderr, "unknown error\n");
        break;
    }
    exit(1);
}