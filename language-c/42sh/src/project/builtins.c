#include "builtins.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "expressions.h"
#include "variable.h"

static char *concat_index(struct ast_command *cmd, size_t right_index)
{
    size_t taille = cmd->size;

    for (size_t index = right_index; index < cmd->size; index++)
        taille += strlen(cmd->argv[index]);

    char *command = calloc(taille, sizeof(char));

    size_t command_index = 0;
    for (size_t i = right_index; i < cmd->size; i++)
    {
        if (strcmp(cmd->argv[i], ""))
        {
            size_t j = 0;
            while (cmd->argv[i][j] != '\0')
                command[command_index++] = cmd->argv[i][j++];
        }

        if (i + 1 < cmd->size && strcmp(cmd->argv[i + 1], ""))
            command[command_index++] = ' ';
    }
    return command;
}

int execute_echo(struct ast_command *cmd)
{
    if (cmd->size == 1)
    {
        printf("\n");
        return 0;
    }
    size_t count_n = 0;
    size_t count_e = 0;

    size_t right_index = 1;
    while (right_index < cmd->size
           && (!strcmp(cmd->argv[right_index], "-e")
               || !strcmp(cmd->argv[right_index], "-n")
               || !strcmp(cmd->argv[right_index], "-en")
               || !strcmp(cmd->argv[right_index], "-ne")))
    {
        if (!strcmp(cmd->argv[right_index], "-e"))
            count_e = 1;
        else if (!strcmp(cmd->argv[right_index], "-n"))
            count_n = 1;
        else
        {
            count_e = 1;
            count_n = 1;
        }
        right_index++;
    }

    char *command_line = concat_index(cmd, right_index);

    if (count_e)
    {
        for (size_t i = 0; i < strlen(command_line); i++)
        {
            if (command_line[i + 1] == '\t')
            {
                i++;
                printf("\t");
            }
            else if (command_line[i + 1] == '\n')
            {
                i++;
                printf("\n");
            }
            else if (command_line[i + 1] == '\\')
            {
                i++;
                printf("\\");
            }
            else if (command_line[i] != 39)
                printf("%c", command_line[i]);
        }
    }
    else
    {
        for (size_t i = 0; i < strlen(command_line); i++)
        {
            if (command_line[i] == '\\')
            {
                printf("%c", command_line[i]);
            }
            else if (command_line[i] != 39)
                printf("%c", command_line[i]);
        }
    }
    if (!count_n)
        printf("\n");

    free(command_line);
    return 0;
}

int execute_exit(struct ast_command *cmd)
{
    if (cmd->size > 2)
        errx(2, "exit: too many arguments\n");

    else if (cmd->size == 1)
        return 0;

    else
        return atoi(cmd->argv[1]) % 256;
}

int execute_cd(struct ast_command *cmd, struct var_list *var)
{
    if (cmd->size > 2)
    {
        fprintf(stderr, "cd: too many arguments");
        return 1;
    }

    int indice_pwd = is_var(var, "PWD");
    int indice_old = is_var(var, "OLDPWD");
    var->list[indice_old]->value[0] =
        getcwd(var->list[indice_old]->value[0], 1024);

    int ret = chdir(cmd->argv[1]);

    if (ret == -1)
    {
        fprintf(stderr, "cd: %s: No such file or directory\n", cmd->argv[1]);
        return 1;
    }
    var->list[indice_pwd]->value[0] =
        getcwd(var->list[indice_pwd]->value[0], 1024);

    return 0;
}

static int exec(struct ast_command *command)
{
    int pid = fork();

    if (pid == -1)
        err(EXIT_FAILURE, NULL);

    command->argv =
        realloc(command->argv, sizeof(char *) * (command->size + 1));
    command->argv[command->size] = NULL;

    if (pid == 0)
    {
        execvp(command->argv[0], command->argv);
        err(127, "failed to execute");
    }

    int wstatus;
    waitpid(pid, &wstatus, 0);
    if (waitpid(pid, &wstatus, 0) == 1)
        err(EXIT_FAILURE, NULL);

    return WEXITSTATUS(wstatus);
}

static void add_exec_command(struct ast_command *cmd, struct ast_command *new)
{
    new->size = 1;
    new->argv[0] = calloc(strlen("builddir/42sh") + 1, sizeof(char));

    char *s = "builddir/42sh";
    size_t index = 0;
    while (s[index] != '\0')
    {
        new->argv[0][index] = s[index];
        index++;
    }

    for (size_t i = 0; i < cmd->size; i++)
    {
        new->argv[i + 1] = calloc(strlen(cmd->argv[i]) + 1, sizeof(char));

        size_t index = 0;
        while (cmd->argv[i][index] != '\0')
        {
            new->argv[i + 1][index] = cmd->argv[i][index];
            index++;
        }

        new->size++;
    }
}

int execute_dot(struct ast_command *cmd)
{
    struct ast_command *new_cmd = malloc(sizeof(struct ast_command));
    new_cmd->argv = malloc(sizeof(char *) * (cmd->size + 1));

    int previous = 0;

    if (!strcmp(cmd->argv[0], "."))
    {
        char *s = "builddir/42sh";
        size_t index = 0;

        while (s[index] != '\0')
        {
            cmd->argv[0][index] = s[index];
            index++;
        }

        free(new_cmd->argv);
        free(new_cmd);
        new_cmd = cmd;
    }
    else
    {
        previous = 1;
        add_exec_command(cmd, new_cmd);
    }

    int res = exec(new_cmd);

    if (previous)
    {
        for (size_t i = 0; i < new_cmd->size; i++)
            free(new_cmd->argv[i]);

        free(new_cmd->argv);
        free(new_cmd);
    }

    return res;
}

int execute_export(struct ast_command *cmd)
{
    char *my_argv = concat_index(cmd, 1);
    char *name = calloc(strlen(cmd->argv[1]) + 1, sizeof(char *));
    char *value = calloc(strlen(cmd->argv[1]) + 1, sizeof(char *));

    size_t indice_cmd = 0;
    size_t indice_name = 0;
    size_t indice_value = 0;

    while (my_argv[indice_cmd] == ' ')
    {
        indice_cmd++;
    }

    while (my_argv[indice_cmd] != '\0' && my_argv[indice_cmd] != '='
           && my_argv[indice_cmd] != ' ')
    {
        name[indice_name++] = my_argv[indice_cmd++];
    }

    if (my_argv[indice_cmd] != ' ')
    {
        fprintf(stderr, "export: : bad variable name\n");
        free(name);
        free(value);
        free(my_argv);
        return 1;
    }

    size_t indice_check = indice_cmd + 1;

    if (my_argv[indice_cmd] == ' ')
    {
        while (my_argv[indice_check] != '\0')
        {
            if (my_argv[indice_check] != ' ' && my_argv[indice_check] != '\0')
            {
                fprintf(stderr, "export: : bad variable name\n");
                free(name);
                free(value);
                free(my_argv);
                return 1;
            }
            indice_check++;
        }
    }

    if (my_argv[indice_cmd] == '\0')
    {
        setenv(name, "", 0);
        free(name);
        free(value);
        free(my_argv);
        return 0;
    }

    indice_cmd++;

    while (my_argv[indice_cmd] != '\0')
    {
        value[indice_value++] = my_argv[indice_cmd++];
    }

    setenv(name, value, 1);

    free(name);
    free(value);
    free(my_argv);

    return 0;
}

int execute_break(struct ast_command *cmd)
{
    if (cmd->size == 1)
        return 1;

    if (cmd->size > 2)
    {
        fprintf(stderr, "break: too many arguments");
        err(2, NULL);
    }

    size_t index = 0;
    while (cmd->argv[1][index] != '\0')
    {
        if (!isdigit(cmd->argv[1][index]))
        {
            fprintf(stderr, "break: %s: numeric argument required",
                    cmd->argv[1]);
            err(2, NULL);
        }
        index++;
    }

    return atoi(cmd->argv[1]);
}

int execute_unset(struct ast_command *cmd, struct var_list *var)
{
    if (is_var(var, cmd->argv[1]) == -1)
        return 0;

    int indice = is_var(var, cmd->argv[1]);

    free(var->list[indice]->value);
    char *value = calloc(1, sizeof(char));

    var->list[indice]->value[0] = value;

    return 0;
}
