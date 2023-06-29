#include <stddef.h>

void heapify_arg(int *array, size_t size, int i)
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

void heapify(int *array, size_t size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify_arg(array, size, i);
}

void heap_sort(int *array, size_t size)
{
    heapify(array, size);

    for (size_t i = size - 1; i > 0; i--)
    {
        int tmp = array[0];
        array[0] = array[i];
        array[i] = tmp;

        heapify_arg(array, i, 0);
    }
}
