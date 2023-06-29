#include "check_alphabet.h"

int check_alphabet(const char *str, const char *alphabet)
{
    if (!alphabet)
        return 1;
    else
    {
        int size_alpha = 0;
        while (alphabet[size_alpha] != '\0')
            size_alpha++;

        for (int i = 0; i < size_alpha; i++)
        {
            int occurence = 0;
            int indice_str = 0;
            while (str[indice_str] != '\0')
            {
                if (str[indice_str] == alphabet[i])
                    occurence++;
                indice_str++;
            }
            if (occurence == 0)
                return 0;
        }
        return 1;
    }
}
