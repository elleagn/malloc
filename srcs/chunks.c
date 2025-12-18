#include "libft_malloc.h"
#include "stdint.h"

t_chunk *find_fitting_chunk(size_t size) {

    t_chunk *current_chunk = arena.heap->bin;
    if (size < 16) {
        size = 16;
    }

    while (current_chunk != NULL) {
        if (current_chunk->size - 8 >= size) {
            remove_chunk(current_chunk, &arena.heap->bin);
            return (current_chunk);
        }
        current_chunk = current_chunk->next_free_chunk;
    }

    return (NULL);
}

t_chunk *resize_chunk(t_chunk *chunk, size_t size) {

    size_t usable_size = size >= 16 ? size : 16;
    if (size % 8 != 0) {
        usable_size = size - size % 8 + 8;
    }
    size_t flags = chunk->size & 7;
    size_t old_size = chunk->size - flags;
    size_t new_size = usable_size + 8;
    if (old_size - new_size < 32) {
        return (chunk);
    }

    chunk->size = new_size + flags;
    size_t remainder_size = old_size - new_size + PREV_INUSE;
    t_chunk *remainder_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size - flags);
    remainder_chunk->size = remainder_size;
    size_t *end_tag = (size_t *)((uintptr_t)remainder_chunk + remainder_chunk->size - PREV_INUSE);
    *end_tag = remainder_chunk->size;
    add_chunk(remainder_chunk, &arena.heap->bin);

    return (chunk);
}
