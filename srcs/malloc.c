#include "libft.h"
#include "libft_malloc.h"
#include <sys/mman.h>


void *malloc(size_t size) {
    void *ptr = NULL;
    if (size <= MAX_SMALL_SIZE) {
        t_chunk *chunk = get_small_chunk(size);
        ptr = (void *)((uintptr_t)chunk + 16);
    } else {
        t_big_chunk *chunk = init_big_chunk(size);
        add_big_chunk(chunk);
        ptr = (void *)((uintptr_t)chunk + 24);
    }
    return ptr;
}
