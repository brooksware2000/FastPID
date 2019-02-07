#ifndef _unittest_h
#define _unittest_h

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr, msg) if (!(expr)) { \
        fprintf(stderr, "* FAILED: "); \
        fprintf(stderr, msg); \
        fprintf(stderr, "\n"); \
        exit(1); \
    }

#endif // _unittest_h
