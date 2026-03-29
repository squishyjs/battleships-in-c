#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Vec2;

void clean_ptr(void *var_ptr) {
    // var_ptr == &int_ptr (int**)
    void *var = *(void**)var_ptr;

    printf("freeing %p\n", var);
    free(var);
}

int main(void) {
    int __attribute__((cleanup(clean_ptr))) *int_ptr = malloc(sizeof(int));
    Vec2 __attribute__((cleanup(clean_ptr))) *vec2_ptr = malloc(sizeof(int));

    *int_ptr = 50;
    printf("int_ptr = %p\n", int_ptr);
    printf("vec2_ptr = %p\n", vec2_ptr);

    if (*int_ptr > 20) {
        return 0;
    }

    return 0;
}
