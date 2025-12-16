#include "libft.h"
#include "libft_malloc.h"
#include <sys/mman.h>

t_arena arena = {NULL};

void *malloc(size_t size) {

    if (!arena.heap)
        arena.heap = initialize_heap();

    t_chunk*chunk = find_fitting_chunk(size);
    void *ptr = resize_chunk(size);
    return (ptr);
}
