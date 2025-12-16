#include "libft_malloc.h"

t_chunk *find_fitting_chunk(size_t size) {

    t_chunk *current_chunk = arena.heap->bin;

    while (current_chunk != NULL) {
        if (current_chunk->size - 8 <= size) {
            remove_chunk(current_chunk, &arena.heap->bin);
            return (current_chunk);
        }
        current_chunk = current_chunk->next_free_chunk;
    }

    return (NULL);
}
