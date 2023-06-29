#include <stddef.h>

void array_max_min(int tab[], size_t len, int *max, int *min)
{
    if (tab == NULL || len == 0)
        return;
    else if (len == 1)
    {
        *max = tab[0];
        *min = tab[0];
    }
    else
    {
        if (tab[1] > tab[0])
        {
            *max = tab[1];
            *min = tab[0];
        }
        else
        {
            *max = tab[0];
            *min = tab[1];
        }
        for (size_t i = 2; i < len; i++)
        {
            if (tab[i] > *max)
                *max = tab[i];
            else if (tab[i] < *min)
                *min = tab[i];
        }
        return;
    }
}
