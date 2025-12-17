#include "libft_malloc.h"
#include "stdio.h"
#include "stdint.h"

#define LINE_WIDTH 50

void print_empty_line() {

    printf("|");
    for (int i = 0; i < LINE_WIDTH; i++) {
        printf(" ");
    }
    printf("|");
}

void print_heap_header() {

    printf("HEAP HEADER\n\n");
    printf("Address = %p\n Size = %lu\n\n", arena.heap, arena.heap->size);
}

void print_chunks() {
    uintptr_t ptr_value = (uintptr_t)arena.heap + 16;
    t_chunk *chunk =  (t_chunk *)ptr_value;
    t_chunk *next_chunk = (t_chunk *)(ptr_value + chunk->size);

    printf("CHUNKS\n\n");
    while ((uintptr_t)next_chunk <= (uintptr_t)arena.heap + arena.heap->size - 8) {
        printf("Address: %p\n", chunk);
        printf("Size: %lu\n", chunk->size);
        if (next_chunk->size % 8 == 0) {
            printf("Free\n");
        } else {
            printf("Used\n");
        }
        ptr_value += chunk->size;
        chunk =  (t_chunk *)ptr_value;
        next_chunk = (t_chunk *)(ptr_value + chunk->size);
    }
    printf("Address: %p\n", chunk);
    printf("Size: %lu\n", chunk->size);
    printf("\n");

}

void print_heap() {
    print_heap_header();
    print_chunks();
}
