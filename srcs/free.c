#include "libft_malloc.h"


void    free(void *ptr) {
    if (ptr == NULL) {
        return ;
    }

    // Retrieve the size of the allocated space, stored right before the pointer
    // address
    // TODO uintptr_t
    size_t size = (size_t)(ptr - sizeof(size_t));

    if (size > MAX_SMALL_SIZE) {
        t_big_chunk *chunk = (t_big_chunk *)(ptr - HEADER);
    }
}
