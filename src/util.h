#ifndef UTIL_H
#define UTIL_H

#define ERR_ALLOC 0
#define ERR_LBEGIN 1
#define ERR_LEND 2
#define ERR_FOPEN 3
#define ERR_ARGS 4
#define ERR_CHMOD 5

void error(int err_type);

#endif