#include <stddef.h>

int vmax(const int *const ptr, size_t size)
{
    int max = 0;
    int vice_max = 0;

    if (*ptr < *(ptr + 1))
    {
        max = *(ptr + 1);
        vice_max = *ptr;
    }
    else
    {
        max = *ptr;
        vice_max = *(ptr + 1);
    }
    for (size_t i = 2; i < size; i++)
    {
        if (*(ptr + i) > max)
        {
            vice_max = max;
            max = *(ptr + i);
        }
        else if (*(ptr + i) > vice_max)
            vice_max = *(ptr + i);
    }
    return vice_max;
}
