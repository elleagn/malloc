#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

#define PREV_INUSE     1
#define MAX_TINY_SIZE  64
#define MAX_SMALL_SIZE 512

#define HEAP_HEADER_SIZE 16

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

typedef struct s_heap {
    size_t size;
    t_chunk *bin;
} t_heap;

typedef struct s_arena {
    t_heap *heap;
} t_arena;

extern t_arena arena;

t_chunk *find_fitting_chunk(size_t size);

/**
 * 
 */
t_chunk *resize_chunk(t_chunk *chunk, size_t size);
void    add_chunk(t_chunk *chunk, t_chunk **bin);
void    remove_chunk(t_chunk *chunk, t_chunk **bin);

t_heap *initialize_heap(void);
void   *malloc(size_t size);

void print_heap();

#endif
