#include "evalexpr.h"

int valid_operator(char s)
{
    char *symbol = "()+-/%*^";

    int index = 0;
    while (symbol[index] != '\0')
    {
        if (s == symbol[index])
            return 1;
        index++;
    }
    return 0;
}
