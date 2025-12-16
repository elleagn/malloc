#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

#define PREV_INUSE 1

typedef struct s_chunk
{
    size_t prev_size;
    size_t size;
}   t_chunk;

typedef struct arena {
    t_chunk *heap;
};

void    *malloc(size_t size);

#endif
