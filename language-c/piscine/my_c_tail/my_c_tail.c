#include <stdlib.h>
#include <unistd.h>

static int my_strlen(char *buffer)
{
    int index = 0;
    while (buffer[index] != '\0')
        index++;
    return index;
}

static unsigned int count_line(char *buffer, size_t size)
{
    unsigned int line = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
            line++;
    }
    return line;
}

static int find_index(char *buffer, unsigned int line)
{
    unsigned int count_carriage = 0;
    int index = 0;
    while (line != count_carriage)
    {
        if (buffer[index++] == '\n')
            count_carriage++;
    }
    return index;
}

void stdintail(unsigned int n)
{
    char character;
    char *buffer = malloc(sizeof(char) * 2000);
    size_t size = 0;

    while (read(0, &character, 1))
        buffer[size++] = character;
    buffer[size] = '\0';

    unsigned int line = count_line(buffer, size);

    if (n >= line)
        write(1, buffer, my_strlen(buffer));
    else
    {
        char *res = buffer + find_index(buffer, line - n);
        write(1, res, my_strlen(res));
    }
    free(buffer);
}
