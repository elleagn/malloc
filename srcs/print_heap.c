#include "libft.h"
#include "libft_malloc.h"
#include "stdint.h"
#include "stdio.h"

#define LINE_WIDTH 50

void print_empty_line() {

    printf("|");
    for (int i = 0; i < LINE_WIDTH; i++) {
        printf(" ");
    }
    printf("|");
}

void print_heap_header(t_segment *heap) {

    printf("HEAP HEADER\n\n");
    printf("Address = %p\n Size = %lu\n\n", heap, heap->size);
}

void print_chunks(t_segment *heap, size_t *size) {
    uintptr_t ptr_value = (uintptr_t)heap + SEGMENT_HEADER_SIZE;
    t_chunk  *chunk = (t_chunk *)ptr_value;

    while (chunk->user_size != 0) {
        if (is_in_use(chunk)) {
            ft_printf("%p - %p : %u bytes %u\n", (uintptr_t)chunk,
                   (uintptr_t)chunk + chunk->size, chunk->user_size, chunk->size);
            *size += chunk->user_size;
        } else {
            ft_printf("%p - %p : %u\n", (uintptr_t)chunk,
                   (uintptr_t)chunk + chunk->size, chunk->size);
        }
        ptr_value += chunk->size - (chunk->size & 7);
        chunk = (t_chunk *)ptr_value;

    }
    ft_printf("last: %p user_size %u size %u\n", chunk, chunk->user_size, chunk->size);
}

void print_heap() {

    size_t     total_size = 0;
    t_segment *heap = arena.tiny_heap;
    ft_printf("TINY : %p\n", (uintptr_t)heap);
    while (heap) {
        print_chunks(heap, &total_size);
        heap = heap->next;
    }
    heap = arena.small_heap;
    ft_printf("SMALL : %p\n", (uintptr_t)heap);
    while (heap) {
        print_chunks(heap, &total_size);
        heap = heap->next;
    }

    t_big_chunk *big_heap = arena.big_heap;
    while (big_heap) {
        ft_printf("LARGE : %p\n", (uintptr_t)big_heap);
        ft_printf("%p - %p : %u bytes\n", (uintptr_t)big_heap,
                   (uintptr_t)big_heap + big_heap->size, big_heap->user_size);
        total_size += big_heap->user_size;
        big_heap = big_heap->next;
    }
    ft_printf("Total : %u bytes\n", total_size);
}
