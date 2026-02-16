#include "libft.h"
#include "libft_malloc.h"
#include "stdint.h"

void sanity_check(t_chunk *chunk) {
    if (chunk == NULL) {
        return;
    }
    if (chunk->user_size == 0) {
        return ;
    }
    if (chunk->size >= 106496 || chunk->user_size >= 106496) {
        ft_printf("chunk: %p - %p size %u user_size %u in_use %i size issue\n", chunk,
                  (uintptr_t)chunk + chunk->size, chunk->size, chunk->user_size,
                  is_in_use(chunk));
        int *ptr = NULL;
        *ptr = 2;
    }
    if ((chunk->size % 8 == 0 && chunk->prev_size > 106496)) {
        ft_printf("chunk: %p - %p size %u user_size %u in_use %i prev_size issue\n", chunk,
                  (uintptr_t)chunk + chunk->size, chunk->size, chunk->user_size,
                  is_in_use(chunk));
        int *ptr = NULL;
        *ptr = 2;
    }
    if (
        is_in_use(chunk) &&
         chunk->user_size > chunk->size - CHUNK_HEADER_SIZE + sizeof(size_t)){
        ft_printf("chunk: %p - %p size %u user_size %u in_use %i user size size issue\n", chunk,
                  (uintptr_t)chunk + chunk->size, chunk->size, chunk->user_size,
                  is_in_use(chunk));
        int *ptr = NULL;
        *ptr = 2;
    }
}

void print_chunks(t_segment *heap, size_t *size) {
    uintptr_t ptr_value = (uintptr_t)heap + SEGMENT_HEADER_SIZE;
    t_chunk  *chunk = (t_chunk *)ptr_value;

    while (chunk->user_size != 0) {
        if (is_in_use(chunk)) {
            ft_printf("%p - %p : %u bytes %u\n", (uintptr_t)chunk,
                      (uintptr_t)chunk + get_chunk_size(chunk),
                      chunk->user_size, chunk->size);
            *size += chunk->user_size;
        } else {
            ft_printf("%p - %p : %u\n", (uintptr_t)chunk,
                      (uintptr_t)chunk + get_chunk_size(chunk), chunk->size);
        }
        ptr_value += get_chunk_size(chunk);
        chunk = (t_chunk *)ptr_value;
        sanity_check(chunk);
    }
    ft_printf("last : user size %u size %u\n", chunk->user_size, chunk->size);
}

void show_alloc_mem() {

    size_t     total_size = 0;
    t_segment *heap = arena.tiny_heap;
    while (heap) {
        ft_printf("TINY : %p size %u\n", (uintptr_t)heap, heap->size);
        print_chunks(heap, &total_size);
        heap = heap->next;
    }
    heap = arena.small_heap;
    while (heap) {
        ft_printf("SMALL : %p size %u\n", (uintptr_t)heap, heap->size);
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
