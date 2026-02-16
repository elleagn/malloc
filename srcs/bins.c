#include "libft_malloc.h"

/**
 * @brief Remove chunk from a list of chunks (tiny or small heap).
 * @param chunk The chunk to remove
 * @param bin Double pointer to the chunk list
 */
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

/**
 * @brief Add chunk to a lost of chunks (tiny or small heap)
 * @param chunk Pointer to the chunk to add
 * @param bin Double pointer to the chunk list
 */
void add_chunk(t_chunk *chunk, t_chunk **bin) {

    chunk->next_free_chunk = *bin;
    chunk->prev_free_chunk = NULL;
    if (*bin != NULL) {
        (*bin)->prev_free_chunk = chunk;
    }
    *bin = chunk;
}
