#include <string.h>
#include <stdio.h>

void *malloc(size_t size);
void print_heap();

int main(void) {
    int *ptr = malloc(sizeof(int));
    *ptr = 15;
    printf("%i\n", *ptr);
    int *ptr2 = malloc(sizeof(int));
    *ptr2 = 19;
    printf("%i %p\n", *ptr, ptr);
    printf("%i %p\n", *ptr2, ptr2);
    print_heap();
    // print_heap();
//    strcpy(ptr, "123");
//    printf("%s\n", ptr);
}
