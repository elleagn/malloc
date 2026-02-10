#include "libft_malloc.h"
#include <sys/mman.h>
#include <unistd.h>

t_arena arena = {NULL, NULL, NULL};

__attribute((constructor)) void init_arena() {
    arena.tiny_heap = initialize_segment(MAX_TINY_SIZE);
    arena.small_heap = initialize_segment(MAX_SMALL_SIZE);
    write(1, "Created\n", 8);
    arena.big_heap = NULL;
}

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

void clean_big_heap(t_big_chunk *chunk) {
    t_big_chunk *next_chunk = chunk->next;
    while (next_chunk != NULL) {
        munmap(chunk, chunk->size);
        chunk = next_chunk;
        next_chunk = chunk->next;
    }
    munmap(chunk, chunk->size);
}

__attribute((destructor)) void free_arena() {
    clean_heap(arena.small_heap);
    clean_heap(arena.tiny_heap);
    if (arena.big_heap != NULL) {
        clean_big_heap(arena.big_heap);
    }
    write(1, "Freed\n", 6);
}
