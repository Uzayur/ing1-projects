#include <stdbool.h>
#include <stddef.h>

bool all(int *array, size_t len, bool (*func)(int))
{
    size_t count = 0;
    size_t index = 0;
    while (index < len)
    {
        if (func(array[index]) == true)
            count++;
        index++;
    }
    if (count == len)
        return true;
    return false;
}
