#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

size_t filter(int *array, size_t len, int **out_array, bool (*func)(int))
{
    size_t out_size = 0;
    size_t index = 0;
    while (index < len)
    {
        if (func(array[index]) == true)
            out_size++;
        index++;
    }

    *out_array = malloc(sizeof(int) * out_size);
    index = 0;
    size_t counter = 0;
    while (counter != out_size)
    {
        if (func(array[index]) == true)
        {
            *(*out_array + counter) = array[index];
            counter++;
        }
        index++;
    }
    return out_size++;
}
