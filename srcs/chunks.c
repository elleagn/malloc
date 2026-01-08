#include "libft_malloc.h"
#include "stdint.h"

/**
 * The strcture of a free chunk being as follow :
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
 *  nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |             Size of chunk, in bytes                           |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Size of next chunk, in bytes                |0|0|0|
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * The minimum usable size is 16 because we must reserve space for the pointers
 * to the next and previous chunk if the chunk is freed + we overwrite the size
 * of chunk of the next byte.
 */
t_chunk *find_fitting_chunk(size_t size, t_segment *heap) {

    t_chunk *bin = heap->bin;
    t_chunk *current_chunk = bin;
    if (size < 16) {
        size = 16;
    }

    // Looking for a chunk that can contain size (usable_size = chunk->size
    // - size of header + previous_size of next_chunk >= size)
    while (current_chunk != NULL) {
        if (size + 8 <= current_chunk->size) {
            remove_chunk(current_chunk, &bin);
            return (current_chunk);
        }
        current_chunk = current_chunk->next_free_chunk;
    }

    heap->next = initialize_segment();
    return (find_fitting_chunk(size, heap->next));
}

t_chunk *resize_chunk(t_chunk *chunk, size_t size, t_chunk **bin) {

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
    size_t remainder_size = old_size - new_size + PREV_INUSE;
    t_chunk *remainder_chunk = (t_chunk *)((uintptr_t)chunk + chunk->size - flags);
    remainder_chunk->size = remainder_size;
    size_t *end_tag = (size_t *)((uintptr_t)remainder_chunk + remainder_chunk->size - PREV_INUSE);
    *end_tag = remainder_chunk->size;
    add_chunk(remainder_chunk, bin);

    return (chunk);
}
