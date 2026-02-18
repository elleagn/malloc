#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "libft_malloc.h"

#include <stdint.h>
#include <stdio.h>
#include "libft/libft.h"

__attribute((constructor)) void init_arena();
__attribute((destructor)) void free_arena();

void test_malloc() {
    ft_printf("malloc / free\n");
    char *ptr = malloc(50);
    free(ptr);
    char *ptr1 = malloc(50);
    show_alloc_mem();
    assert(ptr == ptr1);
    ft_printf("✓ basic functionnality passed\n");

    ft_printf("random malloc / free:\n");
    int seed = time(NULL);
    ft_printf("seed  = %i\n", seed);
    srand(1771402434);
    int *ptrs1[100];
    // int r1s[] = {5, 949, 363, 177, 850, 528};
    // int rs[] = {0, 0, 1, 2, 1, 4};
    // int r2s[] = {0, 612, 992, 372, 90, 857};
    int r;
    for (int i = 0; i < 100; i++) {
        int r1 = rand() % 1000 + 4;
        ft_printf("i = %i malloc %i\n", i, r1);
        ptrs1[i] = malloc(r1);
        if (i != 0) {
            r = rand() % i;
            ft_printf("free ptrs %i\n", r);
            free(ptrs1[r]);
            int r2 = rand() % 1000 + 4;
            ft_printf("ptrs %i malloc %i\n", r, r2);
            ptrs1[r] = malloc(r2);
        }

       *ptrs1[i] = i;
    }
    // for (int i = 0; i < 6; i++) {
    //     int r1 = r1s[i];
    //     ft_printf("i = %i malloc %i\n", i, r1);
    //     ptrs1[i] = malloc(r1);
    //     if (i != 0) {
    //         r = rs[i];
    //         ft_printf("free ptrs %i\n", r);
    //         free(ptrs1[r]);
    //         int r2 = r2s[i];
    //         ft_printf("ptrs %i malloc %i\n", r, r2);
    //         ptrs1[r] = malloc(r2);
    //     }

    //    *ptrs1[i] = i;
    // }
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

void test_realloc_expand_in_place(void) {
    // Allocate 3 chunks, free adjacent ones, realloc should expand
    char *p1 = malloc(50);
    char *p2 = malloc(50);
    char *p3 = malloc(50);

    ft_memset(p1, 'A', 50);
    ft_memset(p2, 'B', 50);
    ft_memset(p3, 'C', 50);

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
    ft_printf("✓ test_realloc_expand_in_place passed\n");
}

void test_realloc_shrink(void) {
    // Shrink within same bin (tiny)
    char *p = malloc(100);
    ft_memset(p, 'X', 100);
    char *p_orig = p;
    (void)p_orig;
    p = realloc(p, 50);

    // Can be in-place or copied, but data must persist
    for (int i = 0; i < 50; i++)
        assert(p[i] == 'X');

    free(p);
    ft_printf("✓ test_realloc_shrink passed\n");
}

void test_realloc_cross_bins(void) {
    // Tiny → Small
    char *p = malloc(50);  // tiny
    ft_memset(p, 'A', 50);

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
    ft_printf("✓ test_realloc_cross_bins passed\n");
}

void test_realloc_exact_fit(void) {
    // Allocate, free neighbors, realloc to exact coalesced size
    char *p1 = malloc(32);
    char *p2 = malloc(64);
    char *p3 = malloc(32);

    ft_memset(p2, 'B', 64);

    free(p1);
    free(p3);

    // p2 is 64 bytes, p1+p3 free on both sides = 32+32 = 64 bytes
    // Realloc to 96 should need coalescing
    p2 = realloc(p2, 96);
    assert(p2 != NULL);
    for (int i = 0; i < 64; i++)
        assert(p2[i] == 'B');

    free(p2);
    ft_printf("✓ test_realloc_exact_fit passed\n");
}

void test_realloc_null_ptr(void) {
    // realloc(NULL, size) should act like malloc
    char *p = realloc(NULL, 100);
    assert(p != NULL);
    ft_memset(p, 'Z', 100);
    free(p);
    ft_printf("✓ test_realloc_null_ptr passed\n");
}

void test_realloc_zero_size(void) {
    // realloc(p, 0) should act like free
    char *p = malloc(100);
    p = realloc(p, 0);
    // p should be NULL or free'd - depends on your implementation
    ft_printf("✓ test_realloc_zero_size passed\n");
}

void test_realloc_no_coalesce_needed(void) {
    // Expand but space already exists in chunk (split remainder)
    char *p = malloc(100);
    ft_memset(p, 'X', 100);

    p = realloc(p, 50);  // shrink
    p = realloc(p, 80);  // grow but may fit in remainder

    for (int i = 0; i < 50; i++)
        assert(p[i] == 'X');

    free(p);
    ft_printf("✓ test_realloc_no_coalesce_needed passed\n");
}

int main(void) {
    test_malloc();
    free_arena();
    init_arena();
    test_realloc_expand_in_place();
    test_realloc_shrink();
    test_realloc_cross_bins();
    test_realloc_exact_fit();
    test_realloc_null_ptr();
    test_realloc_zero_size();
    test_realloc_no_coalesce_needed();

    ft_printf("\nAll realloc tests passed!\n");
    show_alloc_mem();  // Verify no leaks
    return 0;
}
