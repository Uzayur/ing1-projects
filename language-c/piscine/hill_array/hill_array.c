#include <stdio.h>

int top_of_the_hill(int tab[], size_t len)
{
    if (len == 0)
        return -1;
    else
    {
        size_t indice = 0;

        while (tab[indice] <= tab[indice + 1] && indice < len - 1)
            indice++;
        while (tab[indice] >= tab[indice + 1] && indice < len - 1)
            indice++;

        if (indice != len - 1)
            return -1;
        else
        {
            int hill_top = 0;
            for (size_t i = 0; i < len; i++)
            {
                if (tab[i] > tab[hill_top])
                    hill_top = i;
            }
            return hill_top;
        }
    }
    return 0;
}
