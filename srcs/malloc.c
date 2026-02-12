#include "libft.h"
#include "libft_malloc.h"
#include <sys/mman.h>

void *malloc(size_t size) {

    void *ptr = NULL;
    if (size <= MAX_SMALL_SIZE) {
        t_chunk *chunk = get_small_chunk(size);
        ptr = (void *)((uintptr_t)chunk + CHUNK_HEADER_SIZE);
        t_segment *segment = find_right_segment(chunk);
        segment->occupied_bins += 1;
    } else {
        t_big_chunk *chunk = init_big_chunk(size);
        add_big_chunk(chunk);
        ptr = (void *)((uintptr_t)chunk + BIG_CHUNK_HEADER_SIZE);
    }
    return ptr;
}
