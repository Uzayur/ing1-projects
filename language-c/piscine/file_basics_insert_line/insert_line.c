#include <stdio.h>
#include <stdlib.h>

int insert_line(const char *file_in, const char *file_out, const char *content,
                size_t n)
{
    if (!file_in || !file_out)
        return -1;

    FILE *source = fopen(file_in, "r");
    FILE *target = fopen(file_out, "a");

    if (!source || !target)
        return -1;

    size_t index = 0;

    int line_size = 0;
    char *buffer = NULL;
    size_t buffer_size = 250;

    while ((line_size = getline(&buffer, &buffer_size, source)) != -1)
    {
        if (index == n)
            fputs(content, target);
        fputs(buffer, target);
        index++;
        free(buffer);
        buffer = NULL;
    }

    if (index < n)
    {
        while (index++ != n)
            fputs("\n", target);
        fputs(content, target);
    }

    free(buffer);
    return index;
}
