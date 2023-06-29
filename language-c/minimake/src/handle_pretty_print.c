#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handle_rule.h"
#include "handle_var.h"

static int count_var(struct variables *all_var)
{
    int size = 0;
    struct variables *tmp;
    tmp = all_var;

    while (tmp)
    {
        size++;
        tmp = tmp->next;
    }
    free(tmp);
    return size;
}

static void print_each_var(struct variables *all_var, int size)
{
    for (int i = size; i > 0; i--)
    {
        struct variables *tmp;
        tmp = all_var;
        for (int j = 1; j < i; j++)
            tmp = tmp->next;

        int ind = 0;
        printf("'");

        while (isspace(tmp->name[ind]) || tmp->name[ind] == '\t')
            ind++;

        while (tmp->name[ind] != '\0' && tmp->name[ind] != ' '
               && tmp->name[ind] != '\t')
        {
            printf("%c", tmp->name[ind]);
            ind++;
        }
        printf("' = '");

        ind = 0;
        while (tmp->value[ind] == '\t' || isspace(tmp->value[ind]))
            ind++;

        while (tmp->value[ind] != '\0' && tmp->value[ind] != '#'
               && tmp->value[ind] != '\n')
        {
            printf("%c", tmp->value[ind]);
            ind++;
        }
        printf("'\n");
    }
}

static int count_rule(struct rules *all_rule)
{
    int size = 0;
    struct rules *tmp;
    tmp = all_rule;

    while (tmp)
    {
        size++;
        tmp = tmp->next;
    }
    free(tmp);
    return size;
}

static int string_compare(char *name, char *cpy)
{
    int ind_name = 0;
    int ind_cpy = 0;

    while (name[ind_name] == ' ')
        ind_name++;

    while (name[ind_name] != '\0' && cpy[ind_cpy] != '\0')
    {
        if (name[ind_name] != cpy[ind_cpy])
            return 42;
        ind_name++;
        ind_cpy++;
    }
    if (name[ind_name] == '\0' && cpy[ind_cpy] != '\0')
        return 42;
    else if (name[ind_name] != '\0' && cpy[ind_cpy] == '\0')
        return 42;

    return 0;
}

static void var_replace(char *dep, struct variables *all_var, char begin,
                        char end)
{
    int index = 2;
    if (dep[1] == begin)
    {
        while (dep[index] != end && dep[index] != ' ')
            index++;
        if (dep[index] == ' ')
            return;
        else
        {
            char *cpy = malloc(sizeof(char) * (index - 2));
            index = 2;
            while (dep[index] != end)
            {
                cpy[index - 2] = dep[index];
                index++;
            }

            struct variables *tmp;
            tmp = all_var;
            while (tmp)
            {
                if (string_compare(tmp->name, cpy))
                    tmp = tmp->next;
                else
                {
                    printf("[%s]", tmp->value);
                    break;
                }
            }
            free(tmp);
            free(cpy);
            return;
        }
    }
    return;
}

static int print_string_dep(char *dep)
{
    int index = 0;

    int letter = dep[index];
    printf(" [");
    while (letter != '\0' && letter != '#' && letter != '\n')
    {
        printf("%c", letter);
        index++;
        letter = dep[index];
    }
    printf("]");
    if (letter == '#' || letter == '\n')
        return -1;
    return 0;
}

static void print_each_dep(char **dep, struct variables *all_var)
{
    int index = 0;
    while (dep[index])
    {
        int dep_index = 0;
        int letter = dep[index][dep_index];

        if (letter == '$')
        {
            if (dep[index][dep_index + 1] == '(')
                var_replace(dep[index], all_var, '(', ')');
            else
                var_replace(dep[index], all_var, '{', '}');
        }
        else if (letter == '#')
            break;
        else if (strlen(dep[index]) != 1)
        {
            if (print_string_dep(dep[index]) == -1)
                break;
        }
        else
            break;
        index++;
    }
    printf("\n");
}

static void print_each_command(char **command, int size,
                               struct variables *all_var)
{
    for (int index = 0; index < size; index++)
    {
        int count_quote = 0;
        int cmd_ind = 0;
        int letter = command[index][cmd_ind];
        while (letter == ' ' || letter == '\t')
        {
            cmd_ind++;
            letter = command[index][cmd_ind];
        }

        printf("\t'");
        while (letter != '\n' && letter != '\0')
        {
            if (letter == '"')
            {
                printf("%c", letter);
                count_quote++;
            }
            else if (letter == '$' && count_quote != 0)
            {
                if (command[index][cmd_ind + 1] == '(')
                    var_replace(command[index], all_var, '(', ')');
                else
                    var_replace(command[index], all_var, '{', '}');
                printf("%c", letter);
            }
            else
                printf("%c", letter);
            cmd_ind++;
            letter = command[index][cmd_ind];
        }
        printf("'\n");
    }
}

static void print_each_rule(struct rules *all_rule, int size,
                            struct variables *all_var)
{
    for (int i = size; i > 0; i--)
    {
        struct rules *tmp;
        tmp = all_rule;
        for (int j = 1; j < i; j++)
            tmp = tmp->next;

        int ind = 0;
        printf("(");

        while (isspace(tmp->target[ind]))
            ind++;

        while (tmp->target[ind] != '\0' && tmp->target[ind] != ':')
        {
            printf("%c", tmp->target[ind]);
            ind++;
        }
        printf("):");

        print_each_dep(tmp->dep, all_var);

        if (tmp->command)
            print_each_command(tmp->command->command_list, tmp->command->size,
                               all_var);
    }
}

void pretty_print(struct variables *all_var, struct rules *all_rule)
{
    printf("# variables\n");
    print_each_var(all_var, count_var(all_var));

    printf("# rules\n");
    print_each_rule(all_rule, count_rule(all_rule), all_var);
}
