#include <stdlib.h>

static int new_size(char c, const char *str, const char *pattern)
{
    int pattern_size = 0;

    if (pattern != NULL)
    {
        while (pattern[pattern_size] != '\0')
            pattern_size++;
    }

    int size = 0;
    int index = 0;

    while (str[index] != '\0')
    {
        if (str[index] == c)
            size += pattern_size;
        else
            size++;
        index++;
    }

    return size + 1;
}

char *string_replace(char c, const char *str, const char *pattern)
{
    if (!str)
        return NULL;

    char *dest = malloc(sizeof(char) * new_size(c, str, pattern));

    int str_index = 0;
    int dest_index = 0;
    while (str[str_index] != '\0')
    {
        if (str[str_index] == c)
        {
            int pattern_index = 0;
            while (pattern && pattern[pattern_index] != '\0')
            {
                dest[dest_index] = pattern[pattern_index];
                pattern_index++;
                dest_index++;
            }
        }
        else
        {
            dest[dest_index] = str[str_index];
            dest_index++;
        }
        str_index++;
    }
    dest[new_size(c, str, pattern) - 1] = '\0';
    return dest;
}
