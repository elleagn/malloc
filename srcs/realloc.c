#include "libft.h"
#include "libft_malloc.h"
#include <stdint.h>

int is_in_use(t_chunk *chunk) {
    t_chunk *next_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size);
    int      flag = next_chunk->size % 8;
    return (flag);
}

size_t find_free_space(t_chunk *chunk, size_t size) {
    t_chunk *current_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size);
    size_t   potential_size = chunk->size - 8;

    while (!is_in_use(current_chunk) && size > potential_size) {
        potential_size += current_chunk->size;
        current_chunk =
            (t_chunk *)((uintptr_t)current_chunk + current_chunk->size);
    }
    return (potential_size);
}

t_chunk *try_expand_chunk(t_chunk *chunk, t_chunk **bin, size_t size) {
    size_t free_space = find_free_space(chunk, size);
}

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

    if (size < ptr_chunk->size - sizeof(size_t)) {
        new_chunk = split_chunk(ptr_chunk, size, &ptr_heap->bin);
        result = (void *)((uintptr_t)new_chunk + 16);
        return (result);
    }

    new_chunk = try_expand_chunk(ptr_chunk, &ptr_heap->bin, size);
    if (new_chunk != NULL) {
        result = (void *)((uintptr_t)new_chunk + 16);
    } else {
        result = malloc(size);
        ft_memmove(result, ptr, ptr_chunk->size - 8);
        free(ptr);
    }
    return (result);
}
