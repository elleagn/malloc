#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

#define PREV_INUSE     1
#define MAX_TINY_SIZE  64
#define MAX_SMALL_SIZE 512

#define SEGMENT_HEADER_SIZE 24
#define CHUNK_HEADER_SIZE 16
#define BIG_CHUNK_HEADER_SIZE 24

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

/**
 * Big chunks are directly mmaped, and wont be reused so they are automatically
 * unmmaped on free. They are not on consecutive blocks of memory so they are
 * stored in a double linked list, whith their size additionnaly store din the
 * header.
 * The size must be just before the data, so it can be retrieved by looking at
 * the memory right before the pointer whether it is a chunk or big chunk, when
 * calling malloc or realloc on it.
 */

typedef struct s_big_chunk {
    struct s_big_chunk    *next;
    struct s_big_chunk    *prev;
    size_t                size;
}   t_big_chunk;

/**
 * The arena stores the addresses of the different heaps.
 * Allocations smaller than MAX_TINY_SIZE are stored in the tiny_heap and
 * allocations smaller than MAX_SMALL_SIZE are stored in the small_heap.
 * Bigger allocation are stored in big chunks. Each big chunk represents a
 * different mmaped area, they are ummaped as soon as they are free and not
 * reused.
 */

typedef struct s_arena {
    t_segment *tiny_heap;
    t_segment *small_heap;
    t_segment *heap;
    t_big_chunk *big_heap;
} t_arena;

extern t_arena arena;


/**
 * @brief Search for the first fitting chunk in the heap with a usable size
 * >= size, and resize it if necessary
 * @param size The size of the memory requested
 * @return A chunk of the minimal size required to contain data of size size
 */
t_chunk *get_small_chunk(size_t size);

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

t_big_chunk *init_big_chunk(size_t size);
void        add_big_chunk(t_big_chunk *chunk);
void        remove_big_chunk(t_big_chunk *chunk);

/**
 * @brief Request memory for the segment with mmap + fills the header
 * @return The segement, ready to be used
 */
t_segment *initialize_segment(size_t size);
void   *malloc(size_t size);
void    free(void *ptr);
void print_heap();

#endif
