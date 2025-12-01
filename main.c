#include <string.h>
#include <stdio.h>

void *malloc(size_t size);

int main(void) {
    char *ptr = malloc(15);
    (void)ptr;
//    strcpy(ptr, "123");
//    printf("%s\n", ptr);
}
