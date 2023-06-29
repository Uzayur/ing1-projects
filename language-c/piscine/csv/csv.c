#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_number(char *buffer)
{
    int index = 0;
    while (buffer[index] != '\0')
    {
        if (buffer[index] >= '0' && buffer[index] <= '9')
            return 1;
        index++;
    }
    return 0;
}

static int max_number(char *buffer)
{
    int max_number = -50000;

    char *rest = buffer;
    char *tok = strtok_r(rest, ",", &rest);
    while (tok)
    {
        if (atoi(tok) > max_number)
            max_number = atoi(tok);
        tok = strtok_r(rest, ",", &rest);
    }
    return max_number;
}

int main(int argc, char *argv[])
{
    FILE *file;
    if (argc != 2 || !(file = fopen(argv[argc - 1], "r")))
        return 1;

    char *buffer = NULL;
    size_t buffer_size = 200;

    int line_size = 0;
    while ((line_size = getline(&buffer, &buffer_size, file)) != -1)
    {
        if (!count_number(buffer))
            printf("0\n");
        else
            printf("%d\n", max_number(buffer));
    }
    fclose(file);
    free(buffer);
    return 0;
}
