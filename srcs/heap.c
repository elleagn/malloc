#include "libft_malloc.h"
#include "unistd.h"
#include <sys/mman.h>

t_chunk *initialize_heap(void) {

    size_t   page_size = sysconf(_SC_PAGESIZE);
    size_t   heap_size = (100 * MAX_SMALL_SIZE / page_size + 1) * page_size;
    t_chunk *heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANON, -1, 0);
    heap->prev_size = 0;
    heap->size = heap_size + 1;

    return (heap);

}
