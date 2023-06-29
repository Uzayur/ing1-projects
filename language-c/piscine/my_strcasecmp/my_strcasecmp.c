#include <stddef.h>

int my_strcasecmp(const char *s1, const char *s2)
{
    size_t index = 0;

    while (s1[index] != '\0')
    {
        if (s2[index] == '\0')
            return 42;

        char letter_1 = s1[index];
        char letter_2 = s2[index];

        if (letter_1 >= 'A' && letter_1 <= 'Z')
            letter_1 += 'a' - 'A';

        if (letter_2 >= 'A' && letter_2 <= 'Z')
            letter_2 += 'a' - 'A';

        if (letter_1 < letter_2)
            return -42;
        else if (letter_1 > letter_2)
            return 42;
        index++;
    }
    if (s2[index] != '\0')
        return -42;
    return 0;
}
