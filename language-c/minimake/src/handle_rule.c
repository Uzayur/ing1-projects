#include "handle_rule.h"

#include <stdio.h>
#include <stdlib.h>

#include "handle_stack.h"

static int my_strlen_classic(char *buffer)
{
    int size = 0;
    while (buffer[size] != '\0')
        size++;
    return size++;
}

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

static int my_size_end(char *buffer, int begin)
{
    int size = 0;
    while (buffer[begin + size] != '\0' && test_character(buffer[begin + size]))
        size++;
    return size - 1;
}

static int count_dep(char *buffer)
{
    int index = 0;
    while (buffer[index] != ':')
        index++;

    int dep_nbr = 0;

    while (buffer[index] != '\0')
    {
        if (test_character(buffer[index]))
        {
            while (buffer[index] != '\0' && test_character(buffer[index]))
                index++;
            dep_nbr++;
        }
        else
            index++;
    }
    return dep_nbr;
}

static void insert_dep(char *buffer, char *dep_list[])
{
    int index = 0;
    while (buffer[index] != ':')
        index++;

    int dep_list_ind = 0;
    while (buffer[index] != '\0')
    {
        if (test_character(buffer[index]))
        {
            int tmp_index = 0;
            dep_list[dep_list_ind] =
                malloc(sizeof(char) * my_size_end(buffer, index));
            while (buffer[index] != '\0' && test_character(buffer[index]))
            {
                dep_list[dep_list_ind][tmp_index] = buffer[index];
                index++;
                tmp_index++;
            }
            dep_list_ind++;
        }
        else
            index++;
    }
}

static int my_size(char *buffer, int begin)
{
    int size = 0;
    while (test_character(buffer[begin + size]))
        size++;
    return size;
}

static struct commands *add_command(char *buffer, struct commands *command)
{
    char **new_list = malloc(sizeof(*new_list) * (command->size + 1));

    for (int i = 0; i < command->size; i++)
    {
        int size = my_strlen_classic(command->command_list[i]);
        new_list[i] = malloc(sizeof(char) * size);

        int index = 0;
        while (command->command_list[i][index] != '\0')
        {
            new_list[i][index] = command->command_list[i][index];
            index++;
        }
    }

    new_list[command->size] = malloc(sizeof(char) * my_strlen_classic(buffer));
    int index = 0;
    while (buffer[index] != '\0')
    {
        new_list[command->size][index] = buffer[index];
        index++;
    }

    free(command->command_list);
    command->command_list = new_list;
    command->size = command->size + 1;
    return command;
}

struct rules *handle_rule(char *buffer, struct rules *all_rule)
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

    char **dep_list = malloc(sizeof(*dep_list) * count_dep(buffer));
    insert_dep(buffer, dep_list);
    all_rule = stack_push_rule(all_rule, new_name, dep_list);
    return all_rule;
}

struct commands *handle_command(char *buffer, struct commands *command)
{
    if (!command)
    {
        struct commands *new_struct = malloc(sizeof(struct commands));
        new_struct->size = 1;

        char **new_command_list = malloc(sizeof(*new_command_list));

        new_command_list[0] = malloc(sizeof(char) * my_strlen_classic(buffer));

        int index = 0;
        while (buffer[index] != '\0')
        {
            new_command_list[0][index] = buffer[index];
            index++;
        }

        new_struct->command_list = new_command_list;

        return new_struct;
    }
    return add_command(buffer, command);
}
