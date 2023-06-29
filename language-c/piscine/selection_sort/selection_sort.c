#include <stddef.h>

unsigned array_min(const int arr[], unsigned start, unsigned size)
{
    unsigned index_min = start;

    for (unsigned i = start + 1; i < size; i++)
    {
        if (arr[i] < arr[index_min])
            index_min = i;
    }
    return index_min;
}

void swap(int arr[], unsigned i, unsigned j)
{
    int index_i = arr[i];
    int index_j = arr[j];

    arr[i] = index_j;
    arr[j] = index_i;

    return;
}

void selection_sort(int arr[], unsigned size)
{
    if (size == 0)
        return;

    for (unsigned i = 0; i < size - 1; i++)
    {
        if (i != array_min(arr, i, size))
            swap(arr, i, array_min(arr, i, size));
    }
    return;
}
