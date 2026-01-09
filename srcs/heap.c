#include "libft_malloc.h"
#include "unistd.h"
#include <stdint.h>
#include <sys/mman.h>

t_segment *initialize_segment(size_t size) {

    // Calculate the smallest multiple of page size that can contain 100
    // allocations + the header
    size_t page_size = sysconf(_SC_PAGESIZE);
    size_t segment_min_size = 100 * (size + 16) + SEGMENT_HEADER_SIZE;
    size_t segment_size = (segment_min_size / page_size + 1) * page_size;

    t_segment *segment = mmap(NULL, segment_size, PROT_READ | PROT_WRITE,
                           MAP_PRIVATE | MAP_ANON, -1, 0);
    segment->size = segment_size;
    segment->next = NULL;

    // Create a chunk from the empty space
    uintptr_t ptr_value = (uintptr_t)segment;
    t_chunk  *chunk = (t_chunk *)(ptr_value + SEGMENT_HEADER_SIZE);
    segment->bin = chunk;
    chunk->prev_size = 0;
    chunk->size = segment_size - SEGMENT_HEADER_SIZE - 8 + PREV_INUSE;
    chunk->next_free_chunk = NULL;
    chunk->prev_free_chunk = NULL;

    // Put prev_size a the end so the algorithms work for the last chunk
    ptr_value = (uintptr_t)chunk;
    size_t *end_tag = (size_t *)(ptr_value + chunk->size - PREV_INUSE);
    (void)end_tag;
    *end_tag = chunk->size;

    return (segment);
}
