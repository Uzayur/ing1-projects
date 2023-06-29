#include <stddef.h>

int sub(int a, int b)
{
    return a - b;
}

int foldl(int *array, size_t len, int (*func)(int, int))
{
    size_t index = 0;
    while (index < len)
    {
        if (index == 0)
            array[index] = func(0, array[index]);
        else
            array[index] = func(array[index - 1], array[index]);
        index++;
    }
    return array[len - 1];
}
