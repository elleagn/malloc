#include "libft.h"
#include "libft_malloc.h"
#include <stdint.h>

/**
 * @brief Check if a chunk is in use by looking at the prev_size member of the
 * next chunk
 * @param chunk The chunk to assess
 * @return The PREV_INUSE flag of the next chunk
 */
int is_in_use(t_chunk *chunk) {
    t_chunk *next_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size);
    int      flag = next_chunk->size % 8;
    return (flag);
}

/**
 * @brief Check in the following chunks are free, until either the desired size
 * is reached or a used chunk is found
 * @todo END OF THE HEAP
 * @param chunk The chunk after which to look for space
 * @param size The desired total space (including the beginning chunk)
 * @return The potential size of the new chunk
 */
size_t find_free_space(t_chunk *chunk, size_t size) {
    t_chunk *current_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size);
    size_t   potential_size = chunk->size - sizeof(size_t);

    while (!is_in_use(current_chunk) && size > potential_size) {
        potential_size += current_chunk->size;
        current_chunk =
            (t_chunk *)((uintptr_t)current_chunk + current_chunk->size);
    }
    return (potential_size);
}

/**
 * @brief Fuses the chunks next to the given chunks until either a used one is
 * found or the chunk size is bigger than size.
 * @todo chunk expansion
 * @param chunk The chunk to expand
 * @param bin The bin of the chunk's bin, to remove the next chunks if need be
 * @param size The desired size of the new chunk
 */

void *try_expand_chunk(t_chunk *chunk, t_chunk **bin, size_t size) {
    t_chunk *current_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size);
    while (!is_in_use(current_chunk) && size > chunk->size) {
        coalesce_chunk(current_chunk, bin);
        current_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size);
    }
}

/**
 * @todo smaller functions
 */
void *realloc(void *ptr, size_t size) {

    if (ptr == NULL) {
        return (malloc(size));
    }
    if (size == 0) {
        free(ptr);
        return (NULL);
    }

    t_chunk   *ptr_chunk = (t_chunk *)((uintptr_t)ptr - 16);
    t_segment *ptr_heap = find_right_segment(ptr_chunk);
    t_chunk   *new_chunk = NULL;
    t_chunk   *next_chunk = (t_chunk *)((uintptr_t)ptr_chunk + ptr_chunk->size);
    void      *result = NULL;

    // Check if we will go past the heap
    if ((uintptr_t)ptr_chunk + 16 + size <
        (uintptr_t)ptr_heap + ptr_heap->size) {
        try_expand_chunk(ptr_chunk, &ptr_heap->bin, size);
    }
    if (size < ptr_chunk->size - sizeof(size_t)) {
        new_chunk = split_chunk(ptr_chunk, size, &ptr_heap->bin);
        result = (void *)((uintptr_t)new_chunk + 16);
        return (result);
    }

    if (new_chunk != NULL) {
        result = (void *)((uintptr_t)new_chunk + 16);
    } else {
        result = malloc(size);
        ft_memmove(result, ptr, ptr_chunk->size - 8);
        free(ptr);
    }
    return (result);
}
