#include <stddef.h>

int my_strlen(const char *needle)
{
    int size = 0;
    while (needle[size] != '\0')
        size++;
    return size;
}

int my_strstr(const char *haystack, const char *needle)
{
    if (my_strlen(haystack) == 0 || my_strlen(needle) == 0)
        return 0;

    int index_haystack = 0;
    while (haystack[index_haystack] != '\0')
    {
        if (haystack[index_haystack] == needle[0])
        {
            int count = 0;
            int begin = index_haystack;
            while (haystack[begin] == needle[count] && haystack[begin] != '\0')
            {
                count++;
                begin++;
            }
            if (count == my_strlen(needle))
                return index_haystack;
        }
        index_haystack++;
    }
    return -1;
}
