#include <stdlib.h>

#include "heap.h"

struct heap *create_heap(void)
{
    struct heap *new_heap = malloc(sizeof(struct heap));

    new_heap->size = 0;
    new_heap->capacity = 8;

    new_heap->array = malloc(sizeof(int) * 8);

    return new_heap;
}
