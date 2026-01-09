#include "libft.h"
#include "libft_malloc.h"
#include <sys/mman.h>

t_arena arena = {NULL, NULL, NULL};

void *malloc(size_t size) {

    if (!arena.heap) {
        arena.tiny_heap =  initialize_segment(MAX_TINY_SIZE);
        arena.small_heap = initialize_segment(MAX_SMALL_SIZE);
        arena.heap = initialize_segment(1000);
    }

    t_chunk *chunk = get_chunk(size);

    void *ptr = (void *)((uintptr_t)chunk + 16);
    return ptr;

}
