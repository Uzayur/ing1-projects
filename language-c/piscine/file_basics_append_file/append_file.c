#include <stdio.h>

int append_file(const char *file_in, const char *content)
{
    if (!file_in || !content)
        return -1;

    FILE *file;

    file = fopen(file_in, "a");

    fprintf(file, "%s", content);

    fclose(file);

    return 0;
}
