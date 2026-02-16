#include "libft_malloc.h"
#include "stdint.h"



/**
 * @brief Creates a properly formated empty chunk at the given address
 * @param remainder_chunk Address where to create the chunk
 * @param size Size of the newly created chunk
 */
void init_remainder_chunk(t_chunk *remainder_chunk, size_t size, t_chunk **bin) {

    t_chunk *next_chunk = (t_chunk *)((uintptr_t)remainder_chunk + size);
    if (size >= 24) {
        remainder_chunk->size = size + PREV_INUSE;
        remainder_chunk->user_size = remainder_chunk->size;
        remainder_chunk->next_free_chunk = NULL;
        remainder_chunk->prev_free_chunk = NULL;
        next_chunk->prev_size = remainder_chunk->size;
        next_chunk->size = next_chunk->size - next_chunk->size % 8;
        add_chunk(remainder_chunk, bin);
    } else {
        next_chunk->size += 1;
    }
}

/**
 * @brief Resizes the chunk to the minimum possible size that can store an
 * object of size size. The remainder chunk is added to the bin, and the resized
 * chunk is considered as used.
 * @param chunk the chunk to resize
 * @param size the size of the data the new chunk must be able to fit
 * @param bin the bin where to put the remainder chunk
 * @return  Returns chunk
 */
t_chunk *split_chunk(t_chunk *chunk, size_t size, t_chunk **bin) {

    // Size is minimum 24 to be able to store the pointers to the previous +
    // next chunk in the bin when it is freed
    size_t usable_size = size >= 24 ? size : 24;
    if (usable_size % 8 != 0) {
        usable_size = size - size % 8 + 8; // Smallest multiple of 8 >= size
    }
    size_t flags = chunk->size % 8;
    size_t old_size = chunk->size - flags;
    size_t new_size = usable_size + CHUNK_HEADER_SIZE - sizeof(void *);

    t_chunk *next_chunk = (t_chunk *)((uintptr_t)chunk + old_size);
    // Stop if remainder chunk would be smaller than the min free chunk size
    if (old_size - new_size < sizeof(t_chunk)) {
        next_chunk->size += 1;
        return (chunk);
    }

    chunk->size = new_size + flags;
    t_chunk *remainder_chunk =
        (t_chunk *)((uintptr_t)chunk + chunk->size - flags);
    init_remainder_chunk(remainder_chunk, old_size - new_size, bin);
    return (chunk);
}

/**
 * @brief Find the segments containing the given chunk. If no segment is found,
 * NULL is returned.
 * @param chunk Pointer to the chunk of which we want to find the segment
 * @return The segment that the chunks belong to, or NULL if there is no such
 * segment
 */
t_segment *find_right_segment(t_chunk *chunk) {
    t_segment *segment = arena.tiny_heap;
    uintptr_t  chunk_address = (uintptr_t)chunk;
    uintptr_t  segment_address;

    if (chunk->user_size > MAX_TINY_SIZE) {
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

size_t get_chunk_size(t_chunk *chunk) {
    return (chunk->size - chunk->size % 8);
}
