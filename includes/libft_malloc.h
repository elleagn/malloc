#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

#define PREV_INUSE     1
#define MAX_TINY_SIZE  64
#define MAX_SMALL_SIZE 512

#define SEGMENT_HEADER_SIZE 24

/**
 * Reimplementation of a dynamic memory allocator.
 * The heap and chunk structure and their documentation are inspired by glibc malloc
 * (https://github.com/lattera/glibc/blob/master/malloc/malloc.c).
 *
 * Alignment:
 *  - Allocated memory is always 8 bytes aligned
 */

 /**
  * HEAP(S) STRUCTURE
  */

/**
 * Chunks of memory are delimited by a 'boundary tag' (ie the size of free chunks
 * is stored both at the beginning and at the end of each chunk). The last 3 bytes
 * are used as flags (to know if previous chunk was in use).
 *
 * Allocated chunks look like this:
 *
 *  chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Size of previous chunk, if unallocated (P clear)  |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Size of chunk, in bytes                     |0|0|P|
 *     ptr-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             User data                                         .
 *	    .                                                               .
 *	    .                                                               |
 *   nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             (size of chunk, but used for application data)    |
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    |             Size of next chunk, in bytes                |0|0|1|
 *	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * ptr is the address returned to the user.
 * Free chunks are put in bins (circular double linked lists) to facilitate
 * insertion / removal. They look like this:
 *
 *   chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
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
 * PREV_INUSE flag (P) is stored in the lowest byte of the size (which is always
 * a multiple of 8). It is 1 if the previous chunk is used and 0 if it is not.
 */

typedef struct s_chunk {
    size_t          prev_size;
    size_t          size;
    struct s_chunk *next_free_chunk;
    struct s_chunk *prev_free_chunk;
} t_chunk;

/*
    The segment header is stored right before the heap.
    size is the size of the segment, header excluded.
    bin points to a doubly linked list containing all of the free chunks.
    When memory is requested, the programs goes through the list until it finds
    a suitable candidate (ie bigger than the size requested)

*/

typedef struct s_segment {
    size_t              size;
    t_chunk             *bin;
    struct s_segment    *next;
} t_segment;

typedef struct s_arena {
    t_segment *heap;
} t_arena;

extern t_arena arena;

/**
 * @brief Goes through the heap's bin until it finds a chunk with a usable space
 * >= size.
 * @param size the size fo the memory being requested
 * @param bin the bin to go through
 */
t_chunk *find_fitting_chunk(size_t size, t_segment *heap);

/**
 * @brief Resizes the chunk to the minimum possible size that can store an
 * object of size size. The remainder chunk is added to the bin.
 * @param chunk the chunk to resize
 * @param size the size of the data the new chunk must be able to fit
 * @param bin the bin where to put the remainder chunk
 * @return  Returns chunk
 */
t_chunk *resize_chunk(t_chunk *chunk, size_t size, t_chunk **bin);

/**
 * @brief Add chunk to the bin.
 * @param chunk the chunk to be added
 * @param bin the bin (doubly linked list of chunks) to add the chunk to
 */
void    add_chunk(t_chunk *chunk, t_chunk **bin);

/**
 * @brief Remove chunk from the bin.
 * @param chunk the chunk to be removed
 * @param bin the bin (doubly linked list of chunks) to remove the chunk from
 */
void    remove_chunk(t_chunk *chunk, t_chunk **bin);

/**
 * @brief Request memory for the segment with mmap + fills the header
 * @return The segement, ready to be used
 */
t_segment *initialize_segment(void);
void   *malloc(size_t size);

void print_heap();

#endif
