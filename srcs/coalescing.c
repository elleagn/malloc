#include "libft_malloc.h"
#include <stdint.h>


void coalesce_chunk(t_chunk *chunk, t_chunk **bin) {

    size_t flag = chunk->prev_size % 8;
    size_t prev_size = chunk->prev_size - flag;
    size_t size = chunk->size;

    size_t *new_size = (size_t *)((uintptr_t)chunk - (prev_size - 8));
    *new_size = prev_size + size;

    size_t *next_prev_size = (size_t *)((uintptr_t)chunk + size);
    *next_prev_size = *new_size;

    remove_chunk(chunk, bin);
}
