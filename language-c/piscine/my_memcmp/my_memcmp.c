#include <stddef.h>

int my_memcmp(const void *s1, const void *s2, size_t num)
{
    const unsigned char *s1s = s1;
    const unsigned char *s2s = s2;

    size_t index = 0;
    while (s1s[index] == s2s[index] && index <= num - 1)
        index++;

    if (index == num)
        return 0;
    else if (s1s[index] > s2s[index])
        return 42;
    else
        return -42;
}
