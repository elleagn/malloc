#include "libft_malloc.h"

void remove_chunk(t_chunk *chunk, t_chunk **bin) {

    t_chunk *next = chunk->next_free_chunk;
    t_chunk *prev = chunk->prev_free_chunk;

    if (*bin == chunk) {
        bin = next;
    }

    if (next != NULL) {
        next->prev_free_chunk = prev;
    }
    if (prev != NULL) {
        prev->next_free_chunk = next;
    }
}

void add_chunk(t_chunk *chunk, t_chunk **bin) {

    if (*bin == NULL) {
        *bin = chunk;
        return ;
    }

    t_chunk *next = (*bin)->next_free_chunk;
    t_chunk *prev = (*bin);
    chunk->prev_free_chunk = prev;
    chunk->next_free_chunk = next;
    prev->next_free_chunk = chunk;
    next->prev_free_chunk = chunk;
}
