#include "libft.h"
#include "libft_malloc.h"
#include <sys/mman.h>


/**
 * @brief Initializes a big chunk by mapping the necessary memory and
 * initializing the members of the structure
 * @param size The size asked for by the user
 * @return The initialized big chunk
 */
static t_big_chunk *init_big_chunk(size_t size) {

    // Round to the closest multiple of 8
    size_t true_size = size - size % 8 + 8;

    // Map a region of the desired size + space for the header
    t_big_chunk *chunk =
        mmap(NULL, true_size + BIG_CHUNK_HEADER_SIZE, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

    if (chunk != NULL) {
        chunk->next = NULL;
        chunk->prev = NULL;
        chunk->size = true_size + BIG_CHUNK_HEADER_SIZE;
        chunk->user_size = size;
    }

    return (chunk);
}

/**
 * @brief Add a big_chunk to the big heap
 * @param chunk The chunk to add to the list
 */
static void add_big_chunk(t_big_chunk *chunk) {
    if (arena.big_heap == NULL) {
        arena.big_heap = chunk;
        return;
    }

    t_big_chunk *current_chunk = arena.big_heap;
    while (current_chunk->next != NULL) {
        current_chunk = current_chunk->next;
    }
    current_chunk->next = chunk;
    chunk->prev = current_chunk;
}

/**
 * @brief Goes through the heap's bin until it finds a chunk with a usable space
 * >= size.
 * @param size the size fo the memory being requested
 * @param bin the bin to go through
 * @return first chunk big enough to contain the data
 *
 * @details The structure of a free chunk being as follow :
 *  chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Size of previous chunk, if unallocated (P clear)  |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |             Size asked for by the user                        |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |             Size of chunk, in bytes                     |0|0|P|
 *  ptr-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Forward pointer to next chunk in list             |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Back pointer to previous chunk in list            |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Unused space (may be 0 bytes long)                .
 *	    .                                                               .
 *	    .                                                               |
 *  nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |    Size of chunk, in bytes                                    |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |             Size asked for by the user                        |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Size of next chunk, in bytes                |0|0|0|
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * The minimum usable size is 24 because we must reserve space for the pointers
 * to the next and previous chunk if the chunk is freed + we overwrite the size
 * of chunk of the next byte.
 */
static t_chunk *find_fitting_chunk(size_t size, t_chunk **bin) {

    t_chunk *current_chunk = *bin;
    if (size < 24) {
        size = 24;
    }
    t_chunk *previous_chunk = NULL;

    // Looking for a chunk that can contain size (usable_size = chunk->size
    // - size of header + previous_size of next_chunk, ; must be >= size)
    while (current_chunk != NULL) {
        if (size + CHUNK_HEADER_SIZE - sizeof(void *) <= current_chunk->size) {
            remove_chunk(current_chunk, bin);
            return (current_chunk);
        }
        if (current_chunk->size % 8 == 0) {
            previous_chunk = (t_chunk *)((uintptr_t)current_chunk -
                                         current_chunk->prev_size +
                                         current_chunk->prev_size % 8);
            coalesce_chunk(current_chunk, bin);
            current_chunk = previous_chunk;
        } else {
            current_chunk = current_chunk->next_free_chunk;
        }
    }

    return (NULL);
}

/**
 * @brief Search for the first fitting chunk in the heap with a usable size
 * >= size, and resize it if necessary
 * @param size The size of thmalloce memory requested
 * @return A chunk of the minimal size required to contain data of size size
 */
static t_chunk *get_small_chunk(size_t size) {

    t_segment *heap;
    size_t     max_size;
    if (size <= MAX_TINY_SIZE) {
        heap = arena.tiny_heap;
        max_size = MAX_TINY_SIZE;
    } else {
        heap = arena.small_heap;
        max_size = MAX_SMALL_SIZE;
    }

    t_chunk *chunk = find_fitting_chunk(size, &heap->bin);
    sanity_check(chunk);
    // Search through all the existing bins and create a new one if no chunk
    // fits
    while (chunk == NULL) {
        if (heap->next == NULL) {
            heap->next = initialize_segment(max_size);
        }
        heap = heap->next;
        chunk = find_fitting_chunk(size, &heap->bin);
        sanity_check(chunk);
    }

    chunk = split_chunk(chunk, size, &heap->bin);
    sanity_check(chunk);
    return (chunk);
}

/**
 * @brief Allocates size bytes and returns a pointer to the allocated memory.
 * The memory is not initialized.  If size is 0, then malloc() returns NULL.
 * @param size The size to allocate
 */
void *malloc(size_t size) {

    void *ptr = NULL;

    if (size == 0) {
        return (ptr);
    }
    if (size <= MAX_SMALL_SIZE) {
        t_chunk *chunk = get_small_chunk(size);
        sanity_check(chunk);
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
