#include "libft_malloc.h"
#include "stdint.h"

/**
 * @brief Goes through the heap's bin until it finds a chunk with a usable space
 * >= size.
 * @param size the size fo the memory being requested
 * @param bin the bin to go through
 * @return first chunk big enough to contain the data
 *
 * @details The structure of a free chunk being as follow :
 *  chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Size of previous chunk, if unallocated (P clear)  |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |             Size of chunk, in bytes                     |0|0|P|
 *     ptr-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Forward pointer to next chunk in list             |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Back pointer to previous chunk in list            |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Unused space (may be 0 bytes long)                .
 *	    .                                                               .
 *	    .                                                               |
 *  nextchunk->
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ |    Size
 * of chunk, in bytes                           |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Size of next chunk, in bytes                |0|0|0|
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * The minimum usable size is 16 because we must reserve space for the pointers
 * to the next and previous chunk if the chunk is freed + we overwrite the size
 * of chunk of the next byte.
 */
t_chunk *find_fitting_chunk(size_t size, t_chunk **bin) {

    t_chunk *current_chunk = *bin;
    if (size < 16) {
        size = 16;
    }

    // Looking for a chunk that can contain size (usable_size = chunk->size
    // - size of header + previous_size of next_chunk >= size)
    while (current_chunk != NULL) {
        if (size + 8 <= current_chunk->size) {
            remove_chunk(current_chunk, bin);
            return (current_chunk);
        }
        current_chunk = current_chunk->next_free_chunk;
    }

    return (NULL);
}

/**
 * @brief Resizes the chunk to the minimum possible size that can store an
 * object of size size. The remainder chunk is added to the bin.
 * @param chunk the chunk to resize
 * @param size the size of the data the new chunk must be able to fit
 * @param bin the bin where to put the remainder chunk
 * @return  Returns chunk
 */
t_chunk *resize_chunk(t_chunk *chunk, size_t size, t_chunk **bin) {

    // Size is minimum 16 to be able to store the pointers to the previous +
    // next chunk in the bin when it is freed
    size_t usable_size = size >= 16 ? size : 16;
    if (usable_size % 8 != 0) {
        usable_size = size - size % 8 + 8;
    }
    size_t flags = chunk->size & 7;
    size_t old_size = chunk->size - flags;
    size_t new_size = usable_size + 8;
    if (old_size - new_size < 32) {
        return (chunk);
    }

    chunk->size = new_size + flags;
    size_t   remainder_size = old_size - new_size + PREV_INUSE;
    t_chunk *remainder_chunk =
        (t_chunk *)((uintptr_t)chunk + chunk->size - flags);
    remainder_chunk->size = remainder_size;
    size_t *end_tag = (size_t *)((uintptr_t)remainder_chunk +
                                 remainder_chunk->size - PREV_INUSE);
    *end_tag = remainder_chunk->size;
    add_chunk(remainder_chunk, bin);

    return (chunk);
}

t_chunk *get_chunk(size_t size) {

    t_segment *heap;
    size_t      max_size;
    if (size <= MAX_TINY_SIZE) {
        heap = arena.tiny_heap;
        max_size = MAX_TINY_SIZE;
    } else if (size <= MAX_SMALL_SIZE) {
        heap = arena.small_heap;
        max_size = MAX_SMALL_SIZE;
    } else {
        heap = arena.heap;
        max_size = 1000;
    }

    t_chunk *chunk = find_fitting_chunk(size, &heap->bin);

    // Search through all the existing bins and create a new one if no chunk
    // fits
    while (chunk == NULL) {
        if (heap->next == NULL) {
            heap->next = initialize_segment(max_size);
        }
        heap = heap->next;
        chunk = find_fitting_chunk(size, &heap->bin);
    }

    chunk = resize_chunk(chunk, size, &heap->bin);
    return (chunk);
}
