#include <stdbool.h>
#include <stddef.h>

bool any(int *array, size_t len, bool (*func)(int))
{
    size_t count = 0;
    size_t index = 0;
    while (index < len)
    {
        if (func(array[index]) == true)
            count++;
        index++;
    }
    if (count != 0)
        return true;
    return false;
}
