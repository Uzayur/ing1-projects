#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

static void heapify_arg(int *array, size_t size, int i)
{
    int largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < size && array[left] > array[i])
        largest = left;

    if (right < size && array[right] > array[largest])
        largest = right;

    if (i != largest)
    {
        int tmp = array[i];
        array[i] = array[largest];
        array[largest] = tmp;

        heapify_arg(array, size, largest);
    }
}

static void heapify(int *array, size_t size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify_arg(array, size, i);
}

int pop(struct heap *heap)
{
    assert(heap != NULL && heap->size != 0);

    int root = heap->array[0];

    heap->size -= 1;
    heap->array[0] = heap->array[heap->size];

    heapify(heap->array, heap->size);

    return root;
}
