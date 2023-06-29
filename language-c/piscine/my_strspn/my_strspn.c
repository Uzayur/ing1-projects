#include <stddef.h>

int accept_char(char s, const char *accept)
{
    int index = 0;
    while (accept[index] != '\0')
    {
        if (accept[index] == s)
            return 1;
        index++;
    }
    return 0;
}

size_t my_strspn(const char *s, const char *accept)
{
    size_t size = 0;
    while (s[size] != '\0')
        size++;

    for (size_t i = 0; i <= size; i++)
    {
        if (s[i] == '\0')
            return size;
        else if (accept_char(s[i], accept) != 1)
            return i;
    }
    return size;
}
