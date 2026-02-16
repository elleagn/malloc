#include "libft_malloc.h"
#include <sys/mman.h>
#include <unistd.h>

t_arena arena = {NULL, NULL, NULL};

/**
 * @brief Initializes the arena with two mapped and formated empty segments for
 * the tiny and small heap.
 */
__attribute((constructor)) void init_arena() {
    arena.tiny_heap = initialize_segment(MAX_TINY_SIZE);
    arena.small_heap = initialize_segment(MAX_SMALL_SIZE);
    arena.big_heap = NULL;
}

/**
 * @brief Cleans the segment list passed as a parameter by unmapping each
 * segment of the list
 * @param heap First segment of the list to clean
 */
void clean_heap(t_segment *heap) {
    t_segment *current_segment = heap;
    t_segment *next_segment = heap->next;

    while (next_segment != NULL) {
        munmap(current_segment, current_segment->size);
        current_segment = next_segment;
        next_segment = current_segment->next;
    }
    munmap(current_segment, current_segment->size);
}

/**
 * @brief Cleans the big chunk list passed as a parameter by unmapping each
 * memory segment of the list.
 * @param chunk First member of the list to clean
 */
void clean_big_heap(t_big_chunk *chunk) {
    t_big_chunk *next_chunk = chunk->next;
    while (next_chunk != NULL) {
        munmap(chunk, chunk->size);
        chunk = next_chunk;
        next_chunk = chunk->next;
    }
    munmap(chunk, chunk->size);
}

/**
 * @brief Cleanup the arena by unmapping the memory that is still mapped  in the
 * three heaps
 */
__attribute((destructor)) void free_arena() {
    clean_heap(arena.small_heap);
    clean_heap(arena.tiny_heap);
    if (arena.big_heap != NULL) {
        clean_big_heap(arena.big_heap);
    }
}
