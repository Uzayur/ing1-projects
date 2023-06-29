#include <stddef.h>

static int accept_char(char s, const char *accept)
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

static size_t my_strspn(const char *str, const char *accept)
{
    size_t size = 0;
    while (str[size] != '\0')
        size++;

    for (size_t i = 0; i <= size; i++)
    {
        if (str[i] == '\0')
            return size;
        else if (accept_char(str[i], accept) != 1)
            return i;
    }
    return size;
}

static int inside(const char *delim, char c)
{
    int index = 0;
    while (delim[index] != '\0')
    {
        if (delim[index++] == c)
            return 1;
    }
    return 0;
}

static int right_size(char *str, const char *delim)
{
    int size = 0;

    if (!str || !delim)
        return size;

    int index = 0;
    while (str[index] != '\0')
    {
        if (inside(delim, str[index]))
            return size;

        else
        {
            index++;
            size++;
        }
    }
    return size;
}

char *my_strtok_r(char *str, const char *delim, char **saveptr)
{
    if (str == NULL)
        str = *saveptr;

    if (*str == '\0')
    {
        *saveptr = str;
        return NULL;
    }

    str = str + my_strspn(str, delim);
    if (*str == '\0')
    {
        *saveptr = str;
        return NULL;
    }

    char *next_block = str + right_size(str, delim);
    if (*next_block == '\0')
    {
        *saveptr = next_block;
        return str;
    }

    *next_block = '\0';
    *saveptr = next_block + 1;
    return str;
}
