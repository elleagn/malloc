#include "libft_malloc.h"
#include "unistd.h"
#include "libft.h"
#include <stdint.h>
#include <sys/mman.h>

void cleanup_empty_segments(t_segment *heap) {
    t_segment *current_segment = heap;
    t_segment *next_segment = heap->next;
    t_chunk   *first_chunk;

    while (next_segment != NULL) {
        first_chunk = (t_chunk *)((uintptr_t)heap + SEGMENT_HEADER_SIZE);
        if (!is_in_use(first_chunk) &&
            first_chunk->size >= SEGMENT_HEADER_SIZE + 8 - PREV_INUSE) {
                current_segment->next = next_segment->next;
                munmap(next_segment, next_segment->size);
        } else {
            current_segment = next_segment;
        }
        next_segment = current_segment->next;
    }
}

void remove_segment(t_segment *segment, t_segment **heap) {
    if (segment == *heap) {
        *heap = segment->next;
    } else {
        t_segment *current_segment = *heap;
        while (current_segment != NULL && segment != current_segment->next) {
            current_segment = current_segment->next;
        }
        current_segment->next = segment->next;
    }
    munmap(segment, segment->size);
}

t_segment *initialize_segment(size_t size) {

    // Calculate the smallest multiple of page size that can contain 100
    // allocations + the header
    size_t page_size = sysconf(_SC_PAGESIZE);
    size_t segment_min_size = 100 * (size + CHUNK_HEADER_SIZE - 8) + SEGMENT_HEADER_SIZE + CHUNK_HEADER_SIZE;
    size_t segment_size = (segment_min_size / page_size + 1) * page_size;
    ft_printf("page_size: %u, segment_min_size: %u, segment_size: %u\n", page_size, segment_min_size, segment_size);

    t_segment *segment = mmap(NULL, segment_size, PROT_READ | PROT_WRITE,
                              MAP_PRIVATE | MAP_ANON, -1, 0);
    segment->size = segment_size;
    segment->next = NULL;
    segment->occupied_bins = 0;

    // Create a chunk from the empty space
    uintptr_t ptr_value = (uintptr_t)segment;
    t_chunk  *chunk = (t_chunk *)(ptr_value + SEGMENT_HEADER_SIZE);
    segment->bin = chunk;
    chunk->prev_size = 0;
    chunk->user_size = 1;
    chunk->size =
        segment_size - SEGMENT_HEADER_SIZE - CHUNK_HEADER_SIZE + PREV_INUSE; // -8 for end tag
    chunk->next_free_chunk = NULL;
    chunk->prev_free_chunk = NULL;

    // Put prev_size a the end so the algorithms work for the last chunk
    ptr_value = (uintptr_t)chunk;
    t_chunk *last_chunk = (t_chunk *)(ptr_value + chunk->size - PREV_INUSE);
    last_chunk->prev_size = chunk->size;
    last_chunk->user_size = 0;
    last_chunk->size = 0;

    return (segment);
}
