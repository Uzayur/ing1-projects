#include <stddef.h>

void *my_memcpy(void *dest, const void *source, size_t num)
{
    char *cdest = dest;
    const char *csource = source;

    for (size_t i = 0; i < num; i++)
        cdest[i] = csource[i];
    return dest;
}
