#include "libft_malloc.h"
#include "unistd.h"
#include <sys/mman.h>
#include <stdint.h>

t_heap *initialize_heap(void) {

    size_t   page_size = sysconf(_SC_PAGESIZE);
    size_t   heap_size = (100 * (MAX_SMALL_SIZE + 16) / page_size + 1 + HEAP_HEADER_SIZE) * page_size;

    t_heap *heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANON, -1, 0);
    heap->size = heap_size;

    uintptr_t ptr_value = (uintptr_t)heap;
    t_chunk *chunk = (t_chunk *)(ptr_value + HEAP_HEADER_SIZE);
    heap->bin = chunk;
    chunk->prev_size = 0;
    chunk->size = heap_size - HEAP_HEADER_SIZE - 8 + PREV_INUSE;
    chunk->next_free_chunk = NULL;
    chunk->prev_free_chunk = NULL;

    ptr_value = (uintptr_t)chunk;
    size_t *end_tag =(size_t *)(ptr_value + chunk->size - PREV_INUSE);
    (void)end_tag;
    // *end_tag = chunk->size;

    return (heap);

}
