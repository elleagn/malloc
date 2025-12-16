#include "libft_malloc.h"
#include "unistd.h"
#include <sys/mman.h>

t_heap *initialize_heap(void) {

    size_t   page_size = sysconf(_SC_PAGESIZE);
    size_t   heap_size = (100 * (MAX_SMALL_SIZE + 16) / page_size + 1 + 8) * page_size;

    t_heap *heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANON, -1, 0);
    heap->size = heap_size;

    t_chunk *chunk = (t_chunk *)(heap + 8);
    chunk->prev_size = 0;
    chunk->size = heap_size + 1 - 8;

    return (heap);

}
