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

void fuse_next_chunk(t_chunk *chunk, t_chunk **bin) {
    t_chunk *next_chunk =  (t_chunk * )((uintptr_t)chunk + get_chunk_size(chunk));
    int in_use = next_chunk-> size % 8;

    remove_chunk(next_chunk, bin);
    chunk->size += get_chunk_size(next_chunk);
    if (in_use == 0) {
        next_chunk = chunk + get_chunk_size(chunk);
        next_chunk->prev_size = chunk->size;
    }
}

/**
 * @brief Fuses the chunks next to the given chunks until either a used one is
 * found or the chunk size is bigger than size.
 * @todo chunk expansion
 * @param chunk The chunk to expand
 * @param bin The bin of the chunk's bin, to remove the next chunks if need be
 * @param size The desired size of the new chunk
 */

void try_expand_chunk(t_chunk *chunk, t_chunk **bin, size_t size) {
    t_chunk *current_chunk = (t_chunk *)((uintptr_t)chunk + get_chunk_size(chunk));
    while (current_chunk->user_size != 0 && !is_in_use(current_chunk) && size > chunk->size) {
        fuse_next_chunk(chunk, bin);
        current_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size);
    }
}

int belong_to_same_heap(size_t size1, size_t size2) {
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

t_chunk *try_in_place(t_chunk *chunk, size_t size) {
    t_segment *heap = find_right_segment(chunk);
    // t_chunk   *next_chunk = (t_chunk *)((uintptr_t)ptr_chunk + ptr_chunk->size);


    // Check if we will go past the heap

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
    ft_printf("1\n");
    // print_heap();
    ft_printf("\n");

    t_chunk   *new_chunk = NULL;
    t_chunk   *chunk = (t_chunk *)((uintptr_t)ptr - CHUNK_HEADER_SIZE);

     if (belong_to_same_heap(size, get_chunk_size(chunk))) {
        new_chunk = try_in_place(chunk, size);
    }

    ft_printf("2\n");
    // print_heap();
    ft_printf("\n");

    void  *result = NULL;
    if (new_chunk != NULL) {
        new_chunk->user_size = size;
        return ((void *)((uintptr_t)new_chunk + CHUNK_HEADER_SIZE));
    } else {
        result = malloc(size);
        ft_printf("3\n");
        // print_heap();
        ft_printf("\n");
        ft_memmove(result, ptr, chunk->user_size < size ? chunk->user_size : size);
        ft_printf("4\n");
        // print_heap();
        ft_printf("\n");
        free(ptr);
        ft_printf("5\n");
        // print_heap();
        ft_printf("\n");
    }
    return (result);
}
