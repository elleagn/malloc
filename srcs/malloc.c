#include "libft.h"
#include <sys/mman.h>

void *malloc(size_t size) {
    (void)size;
    ft_printf("my malloc\n");
    void *ptr = mmap(NULL, 15, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANON, -1, 0);

    return (ptr);
}
