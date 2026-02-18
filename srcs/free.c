#include "libft_malloc.h"
#include <stdint.h>
#include <sys/mman.h>


/**
 * @brief Remove big chunk from the big heap
 * @param The big chunk to remove
 */
static void remove_big_chunk(t_big_chunk *chunk) {
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

/**
 * @brief Takes a used chunk as argument and makes it a valid free chunk
 * @param chunk The chunk to free
 */
static void make_chunk_free(t_chunk *chunk) {

    if (!is_in_use(chunk)) {
        t_chunk *crash = NULL;
        crash->size = 0;
    }
    chunk->next_free_chunk = NULL;
    chunk->prev_free_chunk = NULL;

    t_chunk *next_chunk = (t_chunk *)((uintptr_t)chunk + get_chunk_size(chunk));

    next_chunk->prev_size = chunk->size;
    next_chunk->size = next_chunk->size - PREV_INUSE;

    t_chunk *second_next_chunk =
        (t_chunk *)((uintptr_t)next_chunk + next_chunk->size);
    if (!is_in_use(next_chunk)) {
        second_next_chunk->prev_size = next_chunk->size;
    }
}

/**
 * @brief Finds the appriopriate segment to add the chunk to + unmaps it if
 * empty. Otherwise add the chunk to the bin. Th chunk is considered empty.
 * @param chunk The chunk to add
 */
void add_chunk_to_heap(t_chunk *chunk) {
    int        heap = chunk->user_size > MAX_TINY_SIZE;
    t_segment *segment = find_right_segment(chunk);
    if (segment == NULL) {
        segment->occupied_bins = 0;
        return;
    }

    segment->occupied_bins -= 1;
    if (segment->occupied_bins == 0 && segment != arena.small_heap &&
        segment != arena.tiny_heap) {
        remove_segment(segment,
                       heap == 0 ? &arena.tiny_heap : &arena.small_heap);
        return;
    }

    add_chunk(chunk, &segment->bin);
}

/**
 * @brief Frees the memory space pointed to by ptr, which must have been
 * returned by a previous call to malloc() or realloc().  Otherwise, or if
 * free(ptr) has already been called before, undefined behavior occurs.  If ptr
 * is NULL, no operation is performed.
 * @param ptr The ptr to free
 */
void free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // Retrieve the size of the allocated space, stored right before the pointer
    // address
    uintptr_t address = (uintptr_t)ptr;
    size_t    user_size = *(size_t *)(address - 2 * sizeof(size_t));

    // In cas of big chunk, just ummap the address and remove it from the list
    if (user_size > MAX_SMALL_SIZE) {
        t_big_chunk *chunk = (t_big_chunk *)(address - BIG_CHUNK_HEADER_SIZE);
        remove_big_chunk(chunk);
        return;
    }

    // Format chunk + adds it to the right segment
    t_chunk *chunk = (t_chunk *)(address - CHUNK_HEADER_SIZE);
    make_chunk_free(chunk);
    add_chunk_to_heap(chunk);
}
