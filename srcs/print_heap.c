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

void print_chunks(t_segment *heap) {
    uintptr_t ptr_value = (uintptr_t)heap + SEGMENT_HEADER_SIZE;
    t_chunk  *chunk = (t_chunk *)ptr_value;
    t_chunk  *next_chunk =
        (t_chunk *)(ptr_value + chunk->size - (chunk->size & 7));

    printf("CHUNKS\n\n");
    while ((uintptr_t)next_chunk <
           (uintptr_t)heap + heap->size - 8) {
        printf("Address: %p\n", chunk);
        printf("Size: %lu\n", chunk->size);
        if (next_chunk->size % 8 == 0) {
            printf("Free\n");
        } else {
            printf("Used\n");
        }
        ptr_value += chunk->size - (chunk->size & 7);
        chunk = (t_chunk *)ptr_value;
        next_chunk = (t_chunk *)(ptr_value + chunk->size - (chunk->size & 7));
    }
    printf("Address: %p\n", chunk);
    printf("Size: %lu\n", chunk->size);
    printf("\n");
}

void print_heap() {

    printf("TINY HEAP\n\n");
    t_segment *heap = arena.tiny_heap;
    while (heap) {
        print_heap_header(heap);
        print_chunks(heap);
        heap = heap->next;
    }
    printf("SMALL HEAP\n\n");
    heap = arena.small_heap;
    while (heap) {
        print_heap_header(heap);
        print_chunks(heap);
        heap = heap->next;
    }
    printf("BIG HEAP\n\n");
    heap = arena.heap;
    while (heap) {
        print_heap_header(heap);
        print_chunks(heap);
        heap = heap->next;
    }
}
