#include <stdio.h>
#include <stdlib.h>

static int close_file(FILE *source, FILE *target)
{
    fclose(source);
    fclose(target);
    return 1;
}

int replace_line(const char *file_in, const char *file_out, const char *content,
                 int n)
{
    FILE *source = fopen(file_in, "r");
    FILE *target = fopen(file_out, "w");

    if (!source)
        return -1;

    char res[1000];
    char rest[1000];
    int res_ind = 0;
    int rest_ind = 0;
    int carriage = 0;

    char c = 'a';
    while ((c = fgetc(source)) != EOF)
    {
        if (carriage < n || n < 0)
            res[res_ind++] = c;
        if (carriage > n)
            rest[rest_ind++] = c;
        if (c == '\n')
            carriage++;
    }

    res[res_ind] = '\0';
    rest[rest_ind] = '\0';

    fputs(res, target);
    if (n < carriage && n >= 0)
    {
        fputs(content, target);
        fputs(rest, target);
    }
    return close_file(source, target);
}
