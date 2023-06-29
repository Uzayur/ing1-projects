#include <stdio.h>

int reverse_content(const char *file_in, const char *file_out)
{
    FILE *source = fopen(file_in, "r");
    FILE *target = fopen(file_out, "w");

    if (!source || !target)
        return -1;

    char buffer[3000] = { 0 };

    char c;
    int index = 0;

    while ((c = fgetc(source)) != EOF)
        buffer[index++] = c;

    index--;
    while (index > -1)
        fputc(buffer[index--], target);

    fclose(source);
    fclose(target);

    return 0;
}
