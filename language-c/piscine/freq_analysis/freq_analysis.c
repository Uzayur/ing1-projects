#include <stdio.h>

size_t len(const char text[])
{
    size_t longueur = 0;
    while (text[longueur] != '\0')
        longueur++;
    return longueur;
}

void freq_analysis(const char text[], const char table[])
{
    int array[26] = { 0 };
    int array_test[26] = { 0 };

    for (size_t i = 0; i < len(text); i++)
    {
        int character = text[i];
        array[character - 65]++;
        array_test[character - 65]++;
    }

    int array_occurence[26] = { 0 };
    for (size_t i = 0; i < len(table); i++)
    {
        int indice_max = 0;
        for (int i = 0; i < 26; i++)
            if (array_test[i] > array_test[indice_max])
                indice_max = i;
        array_occurence[i] = array[indice_max];
        array_test[indice_max] = 0;
    }

    for (int k = 0; k < 26; k++)
    {
        for (size_t i = 0; i < len(table); i++)
        {
            if (array_occurence[i] == array[k])
            {
                printf("%c %c\n", k + 65, table[i]);
            }
        }
    }
}
