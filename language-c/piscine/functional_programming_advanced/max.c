#include <stddef.h>

int int_max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

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

int max(int *array, size_t len)
{
    return foldr(array, len, int_max);
}
