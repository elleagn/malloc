#include <string.h>
#include <stdio.h>
#include "libft_malloc.h"
#include <stdint.h>
void print_heap();

int main(void) {
    t_chunk   *chunk = NULL;
    int *ptr = malloc(sizeof(int));
    *ptr = 15;
    chunk = (t_chunk *)((uintptr_t)ptr - 16);
    int *ptr2 = malloc(sizeof(int));
    free(ptr);
    chunk = (t_chunk *)((uintptr_t)ptr2 - 16);
    *ptr2 = 19;
    void *ptr3 = malloc(52100);
    chunk = (t_chunk *)((uintptr_t)ptr3 - 16);
    void *ptr4 = malloc(52100);
    chunk = (t_chunk *)((uintptr_t)ptr4 - 16);
    // printf("%i %p\n", *ptr, ptr);
    // printf("%i %p\n", *ptr2, ptr2);
    // printf("ptr3 %p\n", ptr3);
    // printf("ptr4 %p\n", ptr4);
    print_heap();
    free(ptr);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    // print_heap();
//    strcpy(ptr, "123");
//    printf("%s\n", ptr);
    int *ptr5 = malloc(10);
    print_heap();
    printf("\n\n\n\n\n");
    ptr5 = realloc(ptr5, 30);
    print_heap();
}
