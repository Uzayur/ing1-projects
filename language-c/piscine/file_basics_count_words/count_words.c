#include <stdio.h>

int count_words(const char *file_in)
{
    FILE *file;
    if (!file_in || !(file = fopen(file_in, "r")))
        return -1;

    int count_words = 0;
    char letter = fgetc(file);
    int test = 0;

    while (letter != EOF)
    {
        if (letter == '\n' || letter == ' ' || letter == '\t')
        {
            if (test == 1)
                count_words++;
            test = 0;
            letter = fgetc(file);
        }
        else
        {
            test = 1;
            letter = fgetc(file);
        }
    }
    fclose(file);
    return count_words + (test > 0);
}
