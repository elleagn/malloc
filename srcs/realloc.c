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
    if (chunk->user_size == 0) {
        return (0);
    }
    t_chunk *next_chunk = (t_chunk *)((uintptr_t)chunk + get_chunk_size(chunk));
    int      flag = next_chunk->size % 8;
    return (flag);
}

/**
 * @brief Fuses the given chunk with the next consecutive one.
 * @param chunk The chunk to fuse
 * @param bin Double pointer to a chunk list from which to remove the right
 * chunk (that is assumed to be free)
 */
static void fuse_next_chunk(t_chunk *chunk, t_chunk **bin) {
    t_chunk *next_chunk = (t_chunk *)((uintptr_t)chunk + get_chunk_size(chunk));

    remove_chunk(next_chunk, bin);
    chunk->size += get_chunk_size(next_chunk);

    next_chunk =(t_chunk *)((uintptr_t)chunk + get_chunk_size(chunk));
    next_chunk->size += PREV_INUSE;

}

/**
 * @brief Fuses the chunks next to the given chunks until either a used one is
 * found or the chunk size is bigger than size.
 * @todo chunk expansion
 * @param chunk The chunk to expand
 * @param bin The bin of the chunk's bin, to remove the next chunks if need be
 * @param size The desired size of the new chunk
 */

static void try_expand_chunk(t_chunk *chunk, t_chunk **bin, size_t size) {
    t_chunk *current_chunk =
        (t_chunk *)((uintptr_t)chunk + get_chunk_size(chunk));
    while (current_chunk->user_size != 0 && !is_in_use(current_chunk) &&
           size > chunk->size) {
        fuse_next_chunk(chunk, bin);
        current_chunk = (t_chunk *)((uintptr_t)chunk + get_chunk_size(chunk));
    }
}

static int belong_to_same_heap(size_t size1, size_t size2) {
    if (size1 > MAX_SMALL_SIZE || size2 > MAX_SMALL_SIZE) {
        return (0);
    }
    if (size1 > MAX_TINY_SIZE && size2 > MAX_TINY_SIZE) {
        return (1);
    }
    if (size1 > MAX_TINY_SIZE || size2 > MAX_TINY_SIZE) {
        return (0);
    }
    return (1);
}

/**
 * @brief Tries to reallocate the memory in place
 * @param chunk chunk to reallocate
 * @param size desired user size
 * @return chunk if the chunk can be realloced in place, NULL otherwise
 */
static t_chunk *try_in_place(t_chunk *chunk, size_t size) {
    t_segment *heap = find_right_segment(chunk);

    try_expand_chunk(chunk, &heap->bin, size);
    if (size < get_chunk_size(chunk) - CHUNK_HEADER_SIZE + sizeof(size_t)) {
        chunk = split_chunk(chunk, size, &heap->bin);
    }
    if (get_chunk_size(chunk) - CHUNK_HEADER_SIZE + sizeof(size_t) >= size) {
        return (chunk);
    }
    return (NULL);
}

/**
 * @brief Changes the size of the memory block pointed to by ptr to size bytes.
 * The contents will be unchanged in the range from the start of the region up
 * to the minimum of the old and new sizes.  If the new size is larger than the
 * old size, the added memory will not be initialized.  If ptr is NULL, then the
 * call is equivalent to malloc(size), for all values of size; if size is equal
 * to zero, and ptr is not NULL, then the call is equivalent to free(ptr).
 * Unless ptr is NULL, it must have been returned by an earlier call to
 * malloc(), or realloc().  If the area pointed to was moved, a free(ptr) is
 * done.
 * @param ptr Pointer to resize
 * @param size size of the new pointer
 * @return The new pointer (or the old one if the memory could be reallocated in
 * place)
 */
void *realloc(void *ptr, size_t size) {

    if (ptr == NULL) {
        return (malloc(size));
    }
    if (size == 0) {
        free(ptr);
        return (NULL);
    }

    t_chunk *new_chunk = NULL;
    t_chunk *chunk = (t_chunk *)((uintptr_t)ptr - CHUNK_HEADER_SIZE);
    size_t min_size = size % 8 == 0 ? size : size - size % 8 + 8;
    if (min_size < 24) {
        min_size = 24;
    }

    if (belong_to_same_heap(min_size, get_chunk_size(chunk))) {
        new_chunk = try_in_place(chunk, min_size);
    }

    void *result = NULL;
    if (new_chunk != NULL) {
        new_chunk->user_size = size;
        return ((void *)((uintptr_t)new_chunk + CHUNK_HEADER_SIZE));
    } else {
        result = malloc(size);
        ft_memmove(result, ptr,
                   chunk->user_size < size ? chunk->user_size : size);
        free(ptr);
    }
    return (result);
}
