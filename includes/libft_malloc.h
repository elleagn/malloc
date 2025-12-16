#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

#define PREV_INUSE 1
#define MAX_TINY_SIZE 64
#define MAX_SMALL_SIZE 512

typedef struct s_chunk
{
    size_t prev_size;
    size_t size;
}   t_chunk;

typedef struct s_heap
{
    size_t size;
} t_heap;


typedef struct s_arena {
    t_heap *heap;
}   t_arena;

extern t_arena arena;


t_heap *initialize_heap(void);
void    *malloc(size_t size);

#endif
