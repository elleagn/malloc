#include "libft_malloc.h"
#include <sys/mman.h>

t_big_chunk *init_big_chunk(size_t size) {

    // Map a region of the desired size + space for the header
    t_big_chunk *chunk =
        mmap(NULL, size + BIG_CHUNK_HEADER_SIZE, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

    if (chunk != NULL) {
        chunk->next = NULL;
        chunk->prev = NULL;
        chunk->size = size + 24;
    }

    return (chunk);
}

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
