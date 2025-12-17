#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

#define PREV_INUSE     1
#define MAX_TINY_SIZE  64
#define MAX_SMALL_SIZE 512

#define HEAP_HEADER_SIZE 16

typedef struct s_chunk {
    size_t          prev_size;
    size_t          size;
    struct s_chunk *next_free_chunk;
    struct s_chunk *prev_free_chunk;
} t_chunk;

typedef struct s_heap {
    size_t size;
    t_chunk *bin;
} t_heap;

typedef struct s_arena {
    t_heap *heap;
} t_arena;

extern t_arena arena;

t_chunk *find_fitting_chunk(size_t size);
t_chunk *resize_chunk(t_chunk *chunk, size_t size);
void    add_chunk(t_chunk *chunk, t_chunk **bin);
void    remove_chunk(t_chunk *chunk, t_chunk **bin);

t_heap *initialize_heap(void);
void   *malloc(size_t size);

void print_heap();

#endif
