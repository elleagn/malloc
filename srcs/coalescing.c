#include "libft_malloc.h"
#include <stdint.h>


/**
 * @brief Coalesce chunk with the previous one. Does not modify the data stored
 * by the previous chunk
 * @param chunk The chunk to fuse with the previous one
 * @param bin The bin that stores the empty chunk, to be able to remove it
 */
t_chunk *coalesce_chunk(t_chunk *chunk, t_chunk **bin) {

    size_t flag = chunk->prev_size % 8;
    size_t prev_size = chunk->prev_size - flag;
    size_t size = chunk->size;
    t_chunk *prev_chunk = (t_chunk *)((uintptr_t)chunk - prev_size);

    prev_chunk->size += size;

    size_t *next_prev_size = (size_t *)((uintptr_t)chunk + size);
    *next_prev_size = prev_chunk->size;

    remove_chunk(chunk, bin);
    return (prev_chunk);
}
