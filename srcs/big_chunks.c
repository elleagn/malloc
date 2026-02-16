#include "libft_malloc.h"
#include <sys/mman.h>

/**
 * @brief Initializes a big chunk by mapping the necessary memory and
 * initializing the members of the structure
 * @param size The size asked for by the user
 * @return The initialized big chunk
 */
t_big_chunk *init_big_chunk(size_t size) {

    // Round to the closest multiple of 8
    size = size - size % 8 + 8;

    // Map a region of the desired size + space for the header
    t_big_chunk *chunk =
        mmap(NULL, size + BIG_CHUNK_HEADER_SIZE, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

    if (chunk != NULL) {
        chunk->next = NULL;
        chunk->prev = NULL;
        chunk->size = size + 24;
        chunk->user_size = size;
    }

    return (chunk);
}

/**
 * @brief Add a big_chunk to the big heap
 * @param chunk The chunk to add to the list
 */
void add_big_chunk(t_big_chunk *chunk) {
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
 * @brief Remove big chunk from the big heap
 * @param The big chunk to remove
 */
void remove_big_chunk(t_big_chunk *chunk) {
    if (chunk->prev == NULL) {
        arena.big_heap = chunk->next;
    } else {
        chunk->prev->next = chunk->next;
    }
    if (chunk->next != NULL) {
        chunk->next->prev = chunk->prev;
    }
    munmap((void *)chunk, chunk->size);
}
