#include "libft_malloc.h"
#include <stdint.h>

t_segment *find_right_segment(t_chunk *chunk) {
    t_segment *segment = arena.tiny_heap;
    uintptr_t  chunk_address = (uintptr_t)chunk;
    uintptr_t  segment_address;

    if (chunk->size - CHUNK_HEADER_SIZE + sizeof(void *) > MAX_TINY_SIZE) {
        segment = arena.small_heap;
    }

    while (segment != NULL) {
        segment_address = (uintptr_t)segment;
        if (segment_address < chunk_address &&
            chunk_address < segment_address + segment->size) {
            return (segment);
        }
        segment = segment->next;
    }

    return (NULL);
}

void free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // Retrieve the size of the allocated space, stored right before the pointer
    // address
    uintptr_t address = (uintptr_t)ptr;
    size_t    size = *(size_t *)(address - sizeof(size_t));

    // In cas of big chunk, just ummap the address and remove it from the list
    if (size - CHUNK_HEADER_SIZE + sizeof(void *) > MAX_SMALL_SIZE) {
        t_big_chunk *chunk = (t_big_chunk *)(address - BIG_CHUNK_HEADER_SIZE);
        remove_big_chunk(chunk);
        return;
    }

    t_chunk  *chunk = (t_chunk *)(address - CHUNK_HEADER_SIZE);
    uintptr_t chunk_address = (uintptr_t)chunk;
    t_chunk *next_chunk = (t_chunk *)(chunk_address + get_chunk_size(chunk));
    uintptr_t next_chunk_address = (uintptr_t)next_chunk;

    // Put back the end boundary tag (ie prev size of the next chunk) + update
    // the next chunk's size end flag (because the previous bloc is free)

    chunk->next_free_chunk = NULL;
    chunk->prev_free_chunk = NULL;
    next_chunk->prev_size = chunk->size;
    next_chunk->size = next_chunk->size - PREV_INUSE;
    size_t *next_end_tag = (size_t *)(next_chunk_address + next_chunk->size);
    *next_end_tag = next_chunk->size;

    // Find the segment with the right address range for the chunk and insert it
    chunk->next_free_chunk = NULL;
    chunk->prev_free_chunk = NULL;
    t_segment *segment = find_right_segment(chunk);
    add_chunk(chunk, &segment->bin);
}
