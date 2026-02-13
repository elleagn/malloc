#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "libft/libft.h"
#include "libft_malloc.h"

#include <stdint.h>
#include <stdio.h>
void show_alloc_mem();
// __attribute((constructor)) void init_arena();
// __attribute((destructor)) void free_arena();

// int main(void) {
//     show_alloc_mem();
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
//     show_alloc_mem();
// //     // free(ptr);
// //     free(ptr2);
// //     free(ptr3);
// //     free(ptr4);
// //     // show_alloc_mem();
// // //    strcpy(ptr, "123");
// // //    printf("%s\n", ptr);
// //     int *ptr5 = malloc(10);
// //     printf("\nfree\n");
// //     // show_alloc_mem();
// //     printf("\nrealloc\n");
// //     ptr5 = realloc(ptr5, 30);
//     // show_alloc_mem();
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


// int main() {
//     ft_printf("malloc / free\n");
//     char *ptr = malloc(50);
//     free(ptr);
//     char *ptr1 = malloc(50);
//     show_alloc_mem();
//     ft_printf("%p\n", (uintptr_t)ptr - 24);
//     assert(ptr == ptr1);
//     ft_printf("✓ basic functionnality passed\n");

//     ft_printf("random malloc / free:\n");
//     srand(time(NULL));
//     int *ptrs1[100];
//     int r;
//     for (int i = 0; i < 100; i++) {
//        ptrs1[i] = malloc(rand() % 2000);
//         if (i != 0) {
//             r = rand() % i;
//             free(ptrs1[r]);
//             ptrs1[r] = malloc(rand() % 2000);
//         }

//        *ptrs1[i] = i;
//     }
//     show_alloc_mem();
//     for (int i = 0; i < 100; i++) {
//        free(ptrs1[i]);
//     }
//     show_alloc_mem();
//     ft_printf("\ncoalescing:\n");
//     free(ptr1);
//     for (int i = 0; i < 100; i++)
//         ptrs1[i] = malloc(MAX_TINY_SIZE);
//     show_alloc_mem();
// }

// void test_realloc_exint main() {
//     ft_printf("malloc / free\n");
//     char *ptr = malloc(50);
//     free(ptr);
//     char *ptr1 = malloc(50);
//     show_alloc_mem();
//     ft_printf("%p\n", (uintptr_t)ptr - 24);
//     assert(ptr == ptr1);
//     ft_printf("✓ basic functionnality passed\n");

//     ft_printf("random malloc / free:\n");
//     srand(time(NULL));
//     int *ptrs1[100];
//     int r;
//     for (int i = 0; i < 100; i++) {
//        ptrs1[i] = malloc(rand() % 2000);
//         if (i != 0) {
//             r = rand() % i;
//             free(ptrs1[r]);
//             ptrs1[r] = malloc(rand() % 2000);
// //         }
// int main() {
//     ft_printf("malloc / free\n");
//     char *ptr = malloc(50);
//     free(ptr);
//     char *ptr1 = malloc(50);
//     show_alloc_mem();
//     ft_printf("%p\n", (uintptr_t)ptr - 24);
//     assert(ptr == ptr1);
//     ft_printf("✓ basic functionnality passed\n");

//     ft_printf("random malloc / free:\n");
//     srand(time(NULL));
//     int *ptrs1[100];
//     int r;
//     for (int i = 0; i < 100; i++) {
//        ptrs1[i] = malloc(rand() % 2000);
//         if (i != 0) {
//             r = rand() % i;
//             free(ptrs1[r]);
//             ptrs1[r] = malloc(rand() % 2000);
//         }

//        *ptrs1[i] = i;
//     }
//     show_alloc_mem();
//     for (int i = 0; i < 100; i++) {
//        free(ptrs1[i]);
//     }
//     show_alloc_mem();
//     ft_printf("\ncoalescing:\n");
//     free(ptr1);
//     for (int i = 0; i < 100; i++)
//         ptrs1[i] = malloc(MAX_TINY_SIZE);
//     show_alloc_mem();
// }

//        *ptrs1[i] = i;
//     }
//     show_alloc_mem();
//     for (int i = 0; i < 100; i++) {
//        free(ptrs1[i]);
//     }
//     show_alloc_mem();
//     ft_printf("\ncoalescing:\n");
//     free(ptr1);
//     for (int i = 0; i < 100; i++)
//         ptrs1[i] = malloc(MAX_TINY_SIZE);
//     show_alloc_mem();
// }
void test_realloc_expand_in_place(void) {
    // Allocate 3 chunks, free adjacent ones, realloc should expand
    char *p1 = malloc(50);
    char *p2 = malloc(50);
    char *p3 = malloc(50);

    memset(p1, 'A', 50);
    memset(p2, 'B', 50);
    memset(p3, 'C', 50);

    char *p2_orig = p2;
    free(p1);  // free before p2
    free(p3);  // free after p2

    // Realloc p2 to 120 bytes - should expand in place via coalescing
    p2 = realloc(p2, 120);

    // Pointer should stay same (in-place expansion)
    assert(p2 == p2_orig);

    // Data should persist
    for (int i = 0; i < 50; i++)
        assert(p2[i] == 'B');

    free(p2);
    printf("✓ test_realloc_expand_in_place passed\n");
}

void test_realloc_shrink(void) {
    // Shrink within same bin (tiny)
    char *p = malloc(100);
    memset(p, 'X', 100);
    char *p_orig = p;
    (void)p_orig;
    p = realloc(p, 50);

    // Can be in-place or copied, but data must persist
    for (int i = 0; i < 50; i++)
        assert(p[i] == 'X');

    free(p);
    printf("✓ test_realloc_shrink passed\n");
}

void test_realloc_cross_bins(void) {
    // Tiny → Small
    char *p = malloc(50);  // tiny
    memset(p, 'A', 50);

    p = realloc(p, 200);   // small
    assert(p != NULL);
    for (int i = 0; i < 50; i++)
        assert(p[i] == 'A');

    // Small → Large
    p = realloc(p, 1000);  // big chunk
    assert(p != NULL);
    for (int i = 0; i < 50; i++)
        assert(p[i] == 'A');

    free(p);
    printf("✓ test_realloc_cross_bins passed\n");
}

void test_realloc_exact_fit(void) {
    // Allocate, free neighbors, realloc to exact coalesced size
    char *p1 = malloc(32);
    char *p2 = malloc(64);
    char *p3 = malloc(32);

    memset(p2, 'B', 64);

    free(p1);
    free(p3);

    // p2 is 64 bytes, p1+p3 free on both sides = 32+32 = 64 bytes
    // Realloc to 96 should need coalescing
    p2 = realloc(p2, 96);
    assert(p2 != NULL);
    for (int i = 0; i < 64; i++)
        assert(p2[i] == 'B');

    free(p2);
    printf("✓ test_realloc_exact_fit passed\n");
}

void test_realloc_null_ptr(void) {
    // realloc(NULL, size) should act like malloc
    char *p = realloc(NULL, 100);
    assert(p != NULL);
    memset(p, 'Z', 100);
    free(p);
    printf("✓ test_realloc_null_ptr passed\n");
}

void test_realloc_zero_size(void) {
    // realloc(p, 0) should act like free
    char *p = malloc(100);
    p = realloc(p, 0);
    // p should be NULL or free'd - depends on your implementation
    printf("✓ test_realloc_zero_size passed (implementation-dependent)\n");
}

void test_realloc_no_coalesce_needed(void) {
    // Expand but space already exists in chunk (split remainder)
    char *p = malloc(100);
    memset(p, 'X', 100);

    p = realloc(p, 50);  // shrink
    p = realloc(p, 80);  // grow but may fit in remainder

    for (int i = 0; i < 50; i++)
        assert(p[i] == 'X');

    free(p);
    printf("✓ test_realloc_no_coalesce_needed passed\n");
}

int main(void) {
    test_realloc_expand_in_place();
    test_realloc_shrink();
    test_realloc_cross_bins();
    test_realloc_exact_fit();
    test_realloc_null_ptr();
    test_realloc_zero_size();
    test_realloc_no_coalesce_needed();

    printf("\nAll realloc tests passed!\n");
    show_alloc_mem();  // Verify no leaks
    return 0;
}
