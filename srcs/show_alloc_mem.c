#include "libft.h"
#include "libft_malloc.h"
#include "stdint.h"


void print_chunks(t_segment *heap, size_t *size) {
    uintptr_t ptr_value = (uintptr_t)heap + SEGMENT_HEADER_SIZE;
    t_chunk  *chunk = (t_chunk *)ptr_value;

    while (chunk->user_size != 0) {
        if (is_in_use(chunk)) {
            ft_printf("%p - %p : %u bytes\n", (uintptr_t)chunk,
                      (uintptr_t)chunk + get_chunk_size(size),
                      chunk->user_size);
            *size += chunk->user_size;
        }
        ptr_value += chunk->size - (chunk->size & 7);
        chunk = (t_chunk *)ptr_value;
    }
}

void show_alloc_mem() {

    size_t     total_size = 0;
    t_segment *heap = arena.tiny_heap;
    while (heap) {
        ft_printf("TINY : %p\n", (uintptr_t)heap);
        print_chunks(heap, &total_size);
        heap = heap->next;
    }
    heap = arena.small_heap;
    while (heap) {
        ft_printf("SMALL : %p\n", (uintptr_t)heap);
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
}
