#include <stddef.h>

void *my_memset(void *s, int c, size_t n)
{
    unsigned char *dest = s;
    size_t index = 0;
    while (index < n)
    {
        dest[index] = c;
        index++;
    }
    return dest;
}
