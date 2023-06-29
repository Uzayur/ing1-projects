#include <stddef.h>
#include <stdlib.h>

static int right_size(const char *s)
{
    int count_letter = 0;
    int index = 0;
    while (s[index] != '\0')
    {
        char letter = s[index];
        int size_block = 0;
        while (s[index] == letter && size_block < 9 && s[index] != '\0')
        {
            size_block++;
            index++;
        }
        count_letter++;
    }
    return count_letter * 2;
}

char *rle_encode(const char *s)
{
    size_t size = 0;
    while (s[size] != '\0')
        size++;

    char *encode = malloc(sizeof(char) * (right_size(s) + 1));
    int occurence = 0;
    int indice_encode = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (s[i] != s[i + 1])
        {
            encode[indice_encode] = '0' + occurence + 1;
            encode[indice_encode + 1] = s[i];
            indice_encode += 2;
            occurence = 0;
        }
        else
        {
            occurence++;
            if (occurence == 9)
            {
                encode[indice_encode] = 48 + occurence;
                encode[indice_encode + 1] = s[i];
                indice_encode += 2;
                occurence = 0;
            }
        }
    }
    encode[right_size(s)] = '\0';
    return encode;
}

char *rle_decode(const char *s)
{
    int number_letter = 0;
    size_t size = 0;
    while (s[size] != '\0')
    {
        if (size % 2 == 0)
        {
            int test = s[size] - 48;
            number_letter += test;
        }
        size++;
    }

    char *decode = malloc(sizeof(char) * number_letter + 1);
    int indice_decode = 0;

    for (size_t i = 0; i < size; i += 2)
    {
        int occurence_letter = 0;
        char letter = s[i + 1];
        while (occurence_letter < s[i] - 48)
        {
            decode[occurence_letter + indice_decode] = letter;
            occurence_letter++;
        }
        indice_decode += s[i] - 48;
    }
    decode[number_letter] = '\0';
    return decode;
}
