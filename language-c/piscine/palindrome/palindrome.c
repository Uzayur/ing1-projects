#include <stddef.h>

int my_strlen(const char *s)
{
    int size = 0;
    while (s[size] != '\0')
        size++;
    return size;
}

int right_begin_index(const char *s, int begin)
{
    while (s[begin] != '\0')
    {
        char letter = s[begin];
        if (letter <= 'z' && letter >= 'a')
            return begin;
        else if (letter <= 'Z' && letter >= 'A')
            return begin;
        begin++;
    }
    return my_strlen(s);
}

int right_end_index(const char *s, int end)
{
    while (end > 0)
    {
        char letter = s[end];
        if (letter >= 'a' && letter <= 'z')
            return end;
        else if (letter >= 'A' && letter <= 'Z')
            return end;
        end--;
    }
    return -1;
}

int palindrome(const char *s)
{
    if (!s)
        return 0;
    else if (my_strlen(s) == 0)
        return 1;

    int begin = 0;
    int end = my_strlen(s) - 1;

    while (begin < end)
    {
        begin = right_begin_index(s, begin);
        end = right_end_index(s, end);
        if (s[begin] != s[end])
            return 0;
        begin++;
        end--;
    }
    return 1;
}
