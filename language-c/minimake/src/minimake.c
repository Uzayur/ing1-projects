#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handle_command.h"
#include "handle_pretty_print.h"
#include "handle_rule.h"
#include "handle_var.h"

static int test_character(char c)
{
    char *s = " :=\t";
    int index = 0;

    while (s[index] != '\0')
    {
        if (s[index] == c)
            return 0;
        index++;
    }
    return 42;
}

static int my_strlen(char *s)
{
    int size = 0;
    while (s[size] != '\0')
        size++;
    return size;
}

static void handle_next(struct rules *all_rule, struct variables *all_var,
int number_p, struct save *all_arg)
{
    if (number_p != 0)
        pretty_print(all_var, all_rule);
    else
        handle_command_exec(all_rule, all_arg);
    free(all_rule);
    free(all_var);
    free(all_arg);
}

static void handle_buffer(char *buffer, FILE *file, int number_p,
struct save *all_arg)
{
    size_t buffer_size = 150;

    struct variables *all_var = NULL;
    struct rules *all_rule = NULL;

    int line_size = getline(&buffer, &buffer_size, file);
    while (line_size != -1)
    {
        if (my_strlen(buffer) != 1)
        {
            int alpha = 0;
            int ind = 0;

            while (buffer[ind] != '\0')
            {
                if (buffer[ind] == '=')
                {
                    all_var = handle_var(buffer, all_var);
                    break;
                }
                else if ((buffer[ind] == '#' && alpha == 0) || buffer[ind] == '"')
                    break;
                else if (buffer[ind] == ':')
                {
                    all_rule = handle_rule(buffer, all_rule);
                    break;
                }
                else if (test_character(buffer[ind]))
                    alpha++;
                ind++;
            }
            if ((alpha != 1 && buffer[ind] == '\0') || buffer[ind] == '"')
                all_rule->command = handle_command(buffer, all_rule->command);
        }
        line_size = getline(&buffer, &buffer_size, file);
    }
    handle_next(all_rule, all_var, number_p, all_arg);
}

static int right_arg(int argc, char *argv[]);

static int existing_file(struct save *all_arg, int number_p)
{
    int index = right_arg(all_arg->argc, all_arg->argv);
    FILE *file;
    while (!(file = fopen(all_arg->argv[index], "r")) && index > 1)
        index--;

    if (index == 1)
        return 2;
    else
    {
        all_arg->filename = all_arg->argv[index];
		char *buffer = NULL;
        handle_buffer(buffer, file, number_p, all_arg);
        fclose(file);
        return 0;
    }
}

static int right_arg(int argc, char *argv[])
{
    int pipe = 0;
    int index = 0;
    while (index != argc)
    {
        if (strcmp(argv[index], "|") == 0)
            pipe = index;
        index++;
    }
    if (pipe == 0)
        return index - 1;
    return pipe - 1;
}

int main(int argc, char *argv[])
{
    struct save *all_arg = malloc(sizeof(struct save));
    all_arg->argc = argc;
    all_arg->argv = argv;
    all_arg->filename = NULL;

    int index_test = 1;
    int last_f = 0;
    int number_p = 0;
    int last_h = 0;

    while (index_test != argc)
    {
        if (strcmp(argv[index_test], "-f") == 0)
            last_f = index_test;
        else if (strcmp(argv[index_test], "-p") == 0)
            number_p++;
        else if (strcmp(argv[index_test], "-h") == 0)
            last_h = index_test;
        index_test++;
    }
    last_f++;
    if (index_test != 0)
    {
        if (right_arg(argc, argv) != last_h && last_h != 0)
            printf("use -f with a valid makefile name.\nuse -p to print it.\n");
        else if (existing_file(all_arg, number_p) == 2)
        {
            printf("The file doesn't exist\n");
            return 2;
        }
    }
    return 0;
}
