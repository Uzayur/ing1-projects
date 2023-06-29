#include "beware_overflow.h"

void *beware_overflow(void *ptr, size_t nmemb, size_t size)
{
    size_t test = 0;
    if (!__builtin_mul_overflow(nmemb, size, &test))
        return (char *)ptr + size * nmemb;
    return NULL;
}
