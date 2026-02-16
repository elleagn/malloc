#include "libft.h"
#include "libft_malloc.h"
#include "unistd.h"
#include <stdint.h>
#include <sys/mman.h>

/**
 * @brief Removes a segment from the given segment list + unmaps it
 * @param segment Pointer to the segment to delete
 * @param heap Double pointer to the first segment of the list from which to
 * remove the segment
 */
void remove_segment(t_segment *segment, t_segment **heap) {
    if (segment == *heap) {
        return;
    } else {
        t_segment *current_segment = *heap;
        while (current_segment != NULL && segment != current_segment->next) {
            current_segment = current_segment->next;
        }
        current_segment->next = segment->next;
    }
    munmap(segment, segment->size);
}

/**
 * @brief Request memory for the segment with mmap + fills the header
 * @param size The max size of an allocation in this segment
 * @return The segment, ready to be used
 */
t_segment *initialize_segment(size_t size) {

    // Calculate the smallest multiple of page size that can contain 100
    // allocations + the header
    size_t page_size = sysconf(_SC_PAGESIZE);
    size_t segment_min_size = 100 * (size + CHUNK_HEADER_SIZE - 8) +
                              SEGMENT_HEADER_SIZE + CHUNK_HEADER_SIZE;
    size_t segment_size = (segment_min_size / page_size + 1) * page_size;

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
    chunk->size = segment_size - SEGMENT_HEADER_SIZE - CHUNK_HEADER_SIZE +
                  PREV_INUSE; // -8 for end tag
    chunk->next_free_chunk = NULL;
    chunk->prev_free_chunk = NULL;

    // Put header at the end so the algorithms work for the last chunk
    ptr_value = (uintptr_t)chunk;
    t_chunk *last_chunk = (t_chunk *)(ptr_value + chunk->size - PREV_INUSE);
    last_chunk->prev_size = chunk->size;
    last_chunk->user_size = 0;
    last_chunk->size = 0;

    return (segment);
}
