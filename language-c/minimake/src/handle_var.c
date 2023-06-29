#include "handle_var.h"

#include <stdio.h>
#include <stdlib.h>

#include "handle_stack.h"

static int test_character(char c)
{
    char *s = " :=";
    int index = 0;

    while (s[index] != '\0')
    {
        if (s[index] == c)
            return 0;
        index++;
    }
    return 42;
}

static int my_size(char *buffer, int begin)
{
    int size = 0;
    while (test_character(buffer[begin + size]))
        size++;

    return size;
}

static int my_size_end(char *buffer, int begin)
{
    int size = 0;
    while (buffer[begin + size] != '\0')
        size++;
    return size - 1;
}

struct variables *handle_var(char *buffer, struct variables *all_var)
{
    int index = 0;

    while (!test_character(buffer[index]))
        index++;

    char *new_name = malloc(sizeof(char) * my_size(buffer, index));
    int final_size = 0;
    while (final_size != my_size(buffer, index))
    {
        new_name[final_size] = buffer[index + final_size];
        final_size++;
    }

    while (buffer[index] != '=')
        index++;
    index++;

    char *new_value = malloc(sizeof(char) * my_size_end(buffer, index));
    final_size = 0;
    while (final_size != my_size_end(buffer, index))
    {
        new_value[final_size] = buffer[index + final_size];
        final_size++;
    }

    all_var = stack_push_var(all_var, new_name, new_value);
    return all_var;
}
