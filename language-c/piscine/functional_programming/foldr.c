#include <stddef.h>

int foldr(int *array, size_t len, int (*func)(int, int))
{
    int index = len - 1;
    array[index] = func(array[index], 0);
    index--;

    while (index >= 0)
    {
        array[index] = func(array[index], array[index + 1]);
        index--;
    }

    return array[0];
}
