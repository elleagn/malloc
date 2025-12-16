#include "libft_malloc.h"

void remove_chunk(t_chunk *chunk) {

    t_chunk *next = chunk->next_free_chunk;
    t_chunk *prev = chunk->prev_free_chunk;

    next->prev_free_chunk = prev;
    prev->next_free_chunk = next;
}

void add_chunk(t_chunk *chunk, t_chunk *bin) {

    chunk->next_free_chunk = bin->next_free_chunk;
    chunk->prev_free_chunk = bin;
    chunk->next_free_chunk->prev_free_chunk = chunk;
    bin->next_free_chunk = chunk;

}
