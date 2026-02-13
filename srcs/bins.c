#include "libft_malloc.h"

void remove_chunk(t_chunk *chunk, t_chunk **bin) {

    t_chunk *next = chunk->next_free_chunk;
    t_chunk *prev = chunk->prev_free_chunk;

    if (*bin == chunk) {
        *bin = next;
    }

    if (next != NULL) {
        next->prev_free_chunk = prev;
    }
    if (prev != NULL) {
        prev->next_free_chunk = next;
    }
}

void add_chunk(t_chunk *chunk, t_chunk **bin) {

    chunk->next_free_chunk = *bin;
    chunk->prev_free_chunk = NULL;
    if (*bin != NULL) {
        (*bin)->prev_free_chunk = chunk;
    }
    *bin = chunk;
}
