#include "libft.h"
#include "libft_malloc.h"
#include <sys/mman.h>

t_arena arena = {NULL};

void *malloc(size_t size) {

    if (!arena.heap) {
        arena.heap = initialize_segment();
    }

    t_chunk *chunk = find_fitting_chunk(size, &arena.heap->bin);
    chunk = resize_chunk(chunk, size, &arena.heap->bin);

    void *ptr = (void *)((uintptr_t)chunk + 16);
    return ptr;

}
