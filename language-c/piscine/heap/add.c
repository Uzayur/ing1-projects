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

void add(struct heap *heap, int val)
{
    if (!heap)
        return;

    if (heap->size < heap->capacity)
    {
        heap->array[heap->size] = val;
        heap->size += 1;
    }
    else
    {
        heap->capacity *= 2;
        heap->array = realloc(heap->array, sizeof(int) * heap->capacity);
        heap->array[heap->size] = val;
        heap->size += 1;
    }
    heapify(heap->array, heap->size);
}
