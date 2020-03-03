#ifndef MEM_C_
#define MEM_C_

#include <stdlib.h>
#include <stdio.h>

void *safe_malloc(size_t n)
{
     void *p = malloc(n);
     if (p == NULL) {
          fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
          exit(-1);
     }
     return p;
}
#endif /* MEM_C_ */
