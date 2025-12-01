#include "libft.h"
#include <sys/mman.h>

void *malloc(size_t size) {

    void *ptr = mmap(NULL, 15, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    (void)size;
    ft_printf("my malloc\n");
    return (ptr);
}
