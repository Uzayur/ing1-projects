#include <stddef.h>

char *my_itoa(int value, char *s)
{
    int index = 0;

    if (value < 0)
    {
        s[index] = '-';
        value = -value;
        index++;
    }

    int index_pui = 10;

    while (value / index_pui > 9)
        index_pui *= 10;

    while (value > 9)
    {
        s[index] = '0' + value / index_pui;
        value = value % index_pui;
        index_pui /= 10;
        index++;
    }
    s[index] = '0' + value;
    s[index + 1] = '\0';
    return s;
}
