#include <stddef.h>

void *my_memmove(void *dest, const void *src, size_t n)
{
    const char *csrc = src;
    char *cdest = dest;
    char tmp[n];

    size_t index = 0;
    while (index < n)
    {
        tmp[index] = csrc[index];
        index++;
    }

    index = 0;
    while (index < n)
    {
        cdest[index] = tmp[index];
        index++;
    }
    return dest;
}
