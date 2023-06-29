#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int my_strlen(char *s)
{
    int size = 0;
    while (s[size] != '\0')
        size++;
    return size;
}

int count_colon_carriage(char *buffer)
{
    int colon = 0;
    int count_alpha = 0;
    int index = 0;
    int carriage = 0;

    while (buffer[index] != '\0')
    {
        int letter = buffer[index];
        if (buffer[index] == ':')
            colon++;
        else if (isalpha(letter))
            count_alpha++;
        else if (buffer[index] == '\r')
            carriage++;
        index++;
    }
    if ((colon != 1 && count_alpha != 0) || carriage != 0)
        return -1;
    return 0;
}

int count_word(char **line_buffer)
{
    int word = 0;
    int index = 0;

    int index_empty = 0;
    while (*(*line_buffer + index_empty) != '\0')
    {
        if (*(*line_buffer + index_empty) != ' ')
            break;
        index_empty++;
    }
    if (index_empty == my_strlen(*line_buffer) - 1)
        return -2;

    while (*(*line_buffer + index) != ':' && *(*line_buffer + index) != '\0')
    {
        int letter = *(*line_buffer + index);
        if (isspace(letter))
            index++;
        else if (isalpha(letter))
        {
            while (isalpha(letter) || letter == '_')
            {
                index++;
                letter = *(*line_buffer + index);
            }
            word++;
        }
    }
    if (*(*line_buffer) == '\0' || word != 1)
        return -1;
    return 0;
}

int handle_buffer(char **line_buffer, int line_size)
{
    int index = 0;
    line_size++;

    if (count_colon_carriage(*line_buffer) == -1)
        return -1;

    if (count_word(line_buffer) == -2)
        return -2;
    if (count_word(line_buffer) == -1)
        return -1;

    while (*(*line_buffer + index) != '\0' && *(*line_buffer + index) != ':')
    {
        int letter = *(*line_buffer);
        if (isspace(letter))
            (*line_buffer)++;

        else if (letter == '=')
            return -1;

        else
            index++;
    }
    return 0;
}

void print_buffer(char **line_buffer)
{
    printf("[");

    int index = 0;
    while (*(*line_buffer + index) != ':' && *(*line_buffer + index) != ' '
           && *(*line_buffer + index) != '\t')
    {
        printf("%c", *(*line_buffer + index));
        index++;
    }

    printf("]:");

    while (*(*line_buffer + index) != '\0')
    {
        int letter = *(*line_buffer + index);

        if (isalpha(letter))
        {
            printf(" (");
            while (isalpha(letter))
            {
                printf("%c", *(*line_buffer + index));
                index++;
                letter = *(*line_buffer + index);
            }
            printf(")");
        }

        index++;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    char *line_buffer = NULL;
    FILE *file = fopen(argv[argc - 1], "r");
    size_t buffer_size = 170;

    if (!file)
        return EXIT_FAILURE;

    int line_size = getline(&line_buffer, &buffer_size, file);
    while (line_size != -1)
    {
        if (my_strlen(line_buffer) != 1)
        {
            int tmp = handle_buffer(&line_buffer, line_size);
            if (tmp == -1)
                return 1;
            else if (tmp != -2)
                print_buffer(&line_buffer);
        }
        line_size = getline(&line_buffer, &buffer_size, file);
    }
    fclose(file);

    return 0;
}
