#include "libft_malloc.h"

t_chunk *find_fitting_chunk(size_t size) {

    void *max_address = arena.heap + arena.heap->size;
    t_chunk *current_chunk = (t_chunk *)(arena.heap + 8);

}
