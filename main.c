#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "libft/libft.h"
#include "libft_malloc.h"

#include <stdint.h>
void print_heap();
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

int main(void) {
    ft_printf("BEGINNING:\n");
    print_heap();

    ft_printf("\nTINY MALLOC (10)\n");
    void *ptr = malloc(10);
    (void)ptr;
    print_heap();

    ft_printf("\n2 HEAPS\n");
    int *ptrs[120];
    for (int i = 0; i <= 120; i++) {
       ptrs[i] = malloc(50);
       *ptrs[i] = i;
    }
    print_heap();

    ft_printf("\nFREE \n");
    for (int i = 120; i >= 0; i--) {
        free(ptrs[i]);
    }
    print_heap();

    ft_printf("\nCOALESCING\n");
    void *ptr1 = malloc(64);
    void *ptr2 = malloc(64);
    (void)ptr1;
    (void)ptr2;
    print_heap();

    srand(time(NULL));
    int *ptrs1[100];
    for (int i = 0; i < 100; i++) {
       ptrs1[i] = malloc(rand() % 1000);
       *ptrs1[i] = i;
    }
    print_heap();

}
