#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "libft/libft.h"
#include "libft_malloc.h"

#include <stdint.h>
void show_alloc_mem();
// __attribute((constructor)) void init_arena();
// __attribute((destructor)) void free_arena();

// int main(void) {
//     print_heap();
//     printf("\nmalloc\n");
//     int *ptr = malloc(sizeof(int));
//     *ptr = 15;

//     int *ptr2 = malloc(sizeof(int));
//    // free(ptr);
//     *ptr2 = 19;
//     // void *ptr3 = malloc(52100);
// //     void *ptr4 = malloc(52100);
// //     chunk = (t_chunk *)((uintptr_t)ptr4 - 16);
// //     // printf("%i %p\n", *ptr, ptr);
// //     // printf("%i %p\n", *ptr2, ptr2);
// //     // printf("ptr3 %p\n", ptr3);
// //     // printf("ptr4 %p\n", ptr4);
//     print_heap();
// //     // free(ptr);
// //     free(ptr2);
// //     free(ptr3);
// //     free(ptr4);
// //     // print_heap();
// // //    strcpy(ptr, "123");
// // //    printf("%s\n", ptr);
// //     int *ptr5 = malloc(10);
// //     printf("\nfree\n");
// //     // print_heap();
// //     printf("\nrealloc\n");
// //     ptr5 = realloc(ptr5, 30);
//     // print_heap();
// }

// int main(void) {
//     ft_printf("BEGINNING:\n");
//     show_alloc_mem();

//     ft_printf("\nTINY MALLOC (10)\n");
//     void *ptr = malloc(10);
//     (void)ptr;
//     show_alloc_mem();

//     ft_printf("\n2 HEAPS\n");
//     int *ptrs[120];
//     for (int i = 0; i <= 120; i++) {
//        ptrs[i] = malloc(50);
//        *ptrs[i] = i;
//     }
//     show_alloc_mem();

//     ft_printf("\nFREE \n");
//     for (int i = 120; i >= 0; i--) {
//         free(ptrs[i]);
//     }
//     show_alloc_mem();

//     ft_printf("\nCOALESCING\n");
//     void *ptr1 = malloc(64);
//     void *ptr2 = malloc(64);
//     (void)ptr1;
//     (void)ptr2;
//     show_alloc_mem();

//     srand(time(NULL));
//     int *ptrs1[100];
//     for (int i = 0; i < 100; i++) {
//        ptrs1[i] = malloc(rand() % 1000);
//        *ptrs1[i] = i;
//     }
//     show_alloc_mem();

// }


int main() {
    ft_printf("malloc / free\n");
    char *ptr = malloc(50);
    free(ptr);
    char *ptr1 = malloc(50);
    show_alloc_mem();
    ft_printf("%p\n", (uintptr_t)ptr - 24);
    assert(ptr == ptr1);
    ft_printf("✓ basic functionnality passed\n");

    ft_printf("random malloc / free:\n");
    srand(time(NULL));
    int *ptrs1[100];
    int r;
    for (int i = 0; i < 100; i++) {
       ptrs1[i] = malloc(rand() % 2000);
        if (i != 0) {
            r = rand() % i;
            free(ptrs1[r]);
            ptrs1[r] = malloc(rand() % 2000);
        }

       *ptrs1[i] = i;
    }
    show_alloc_mem();
    for (int i = 0; i < 100; i++) {
       free(ptrs1[i]);
    }
    show_alloc_mem();
    ft_printf("\ncoalescing:\n");
    free(ptr1);
    for (int i = 0; i < 100; i++)
        ptrs1[i] = malloc(MAX_TINY_SIZE);
    show_alloc_mem();
}
