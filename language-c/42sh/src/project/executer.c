#include "executer.h"

#include <unistd.h>

#include "builtins.h"
#include "expressions.h"
#include "free.h"
#include "parser.h"
#include "variable.h"

int exit_value = -1;

static int exec_builtins(struct ast_command *command, struct var_list *var);
static int exec_pipe(struct ast_node *left, struct ast_node *right,
                     struct var_list *var_list);

static void command_replace(char *name, char **command, size_t index,
                            struct var_list *var)
{
    char *value = "";
    if (is_var(var, name) != -1)
        value = var->list[is_var(var, name)]->value[0];
    else if (getenv(name) != NULL)
        value = getenv(name);

    size_t cmd_ind = 0;
    size_t new_cmd_ind = 0;
    char *new_command = calloc(1024, sizeof(char));

    while (42)
    {
        if (command[index][cmd_ind] == '$')
        {
            char stop = command[index][cmd_ind + 1];
            size_t value_ind = 0;

            while (value[value_ind] != '\0' && value[value_ind] != '$')
                new_command[new_cmd_ind++] = value[value_ind++];

            cmd_ind += strlen(name) + 1 + 2 * (stop == '{');

            break;
        }
        else
            new_command[new_cmd_ind++] = command[index][cmd_ind++];
    }

    while (command[index][cmd_ind] != '\0' && command[index][cmd_ind] != '"')
        new_command[new_cmd_ind++] = command[index][cmd_ind++];

    size_t index_bis = 0;
    while (new_command[index_bis] != '\0')
    {
        command[index][index_bis] = new_command[index_bis];
        index_bis++;
    }
    command[index][index_bis] = '\0';

    free(new_command);
}

static void expand_var(struct ast_command *ast_command, struct var_list *var)
{
    for (size_t i = 0; i < ast_command->size; i++)
    {
        char *command = ast_command->argv[i];
        size_t cmd_ind = 0;
        while (command[cmd_ind] != '\0')
        {
            if (command[cmd_ind] == '"' && cmd_ind == 0)
            {
                size_t index = cmd_ind;

                while (command[index] != '\0')
                {
                    ast_command->argv[i][index] =
                        ast_command->argv[i][index + 1];
                    index++;
                }
            }

            else if (command[cmd_ind] == '$')
            {
                char *word = calloc(512, sizeof(char));
                size_t ind_word = 0;

                char stop = ' ';
                if (command[cmd_ind + 1] == '{')
                {
                    cmd_ind += 2;
                    stop = '}';
                }
                else
                    cmd_ind++;

                while (command[cmd_ind] != '\0' && command[cmd_ind] != stop
                       && command[cmd_ind] != '=' && command[cmd_ind] != '\n'
                       && command[cmd_ind] != '"')
                    word[ind_word++] = command[cmd_ind++];

                if (command[cmd_ind] == '\0' && stop == '}')
                    errx(1, "error: bad substitution");

                cmd_ind += (stop == '}');

                command_replace(word, ast_command->argv, i, var);

                free(word);
            }

            else if (command[cmd_ind] == '"')
                cmd_ind++;

            else
                cmd_ind++;
        }
    }
}

/*
static char *concat(struct ast_node *node)
{
    size_t taille = node->data->ast_command->size;
    for (size_t index = 0; index < node->data->ast_command->size; index++)
    {
        taille += strlen(node->data->ast_command->argv[index]);
    }
    char *command = malloc(taille * sizeof(char));
    size_t index = 0;
    for (size_t i = 0; i < node->data->ast_command->size; i++)
    {
        size_t j = 0;
        while (node->data->ast_command->argv[i][j] != '\0')
        {
            command[index] = node->data->ast_command->argv[i][j];
            index++;
            j++;
        }
        command[index] = ' ';
        index++;
    }
    command[index - 1] = '\0';
    return command;
}
*/

static int check_redirection(struct ast_node *node)
{
    struct ast_command *com = node->data->ast_command;
    size_t index = 0;
    char *tmp = com->argv[0];
    while (index < com->size)
    {
        tmp = com->argv[index];
        if (!strcmp(tmp, ">"))
            return 1;
        else if (!strcmp(tmp, "<"))
            return 2;
        else if (!strcmp(tmp, ">&"))
            return 3;
        else if (!strcmp(tmp, "<&"))
            return 4;
        else if (!strcmp(tmp, ">>"))
            return 5;
        else if (!strcmp(tmp, "<>"))
            return 6;
        else if (!strcmp(tmp, ">|"))
            return 7;
        index++;
    }
    return 0;
}

static int exec_redirection(struct ast_node *node, int type,
                            struct var_list *var)
{
    struct ast_command *com = node->data->ast_command;
    int stdout_dup = dup(STDOUT_FILENO);

    if (type == 1 || type == 3 || type == 5 || type == 7)
    {
        int file_fd = 0;
        if (type == 1 || (type == 3 && isalpha(com->argv[com->size - 1][0]))
            || type == 7)
            file_fd = open(com->argv[com->size - 1],
                           O_CREAT | O_TRUNC | O_WRONLY, 0644);

        else if (type == 3 && isdigit(com->argv[com->size - 1][0]))
            file_fd = atoi(com->argv[com->size - 1]);

        else if (type == 5)
            file_fd = open(com->argv[com->size - 1],
                           O_CREAT | O_APPEND | O_WRONLY, 0644);

        if (file_fd == -1)
            err(1, "open failed");

        if (dup2(file_fd, STDOUT_FILENO) == -1)
            err(1, "dup2 failed");
    }

    size_t index = 0;
    while (com->argv[index][0] != '>')
        index++;
    com->argv[index] = NULL;
    com->size = index; // heap buffer

    int res = exec_builtins(com, var);

    fflush(stdout);
    dup2(stdout_dup, STDOUT_FILENO);
    close(stdout_dup);

    return res;
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

static int exec_builtins(struct ast_command *command, struct var_list *var)
{
    if (!strcmp(command->argv[0], "echo"))
        return execute_echo(command);

    else if (!strcmp(command->argv[0], "exit"))
    {
        exit_value = execute_exit(command);
        return exit_value;
    }
    else if (!strcmp(command->argv[0], "break"))
    {
        exit_value = 300 + execute_break(command);
        return 0;
    }
    else if (!strcmp(command->argv[0], "cd"))
        return execute_cd(command, var);

    else if (command->argv[0][0] == '.')
        return execute_dot(command);

    else if ((!strcmp(command->argv[0], "export")))
        return execute_export(command);

    else
        return exec(command);
}

static int exec_command(struct ast_node *node, struct var_list *var_list)
{
    if (search_var(node->data->ast_command->argv[0], var_list))
        return 0;

    expand_var(node->data->ast_command, var_list);
    if (check_redirection(node))
        return exec_redirection(node, check_redirection(node), var_list);
    return exec_builtins(node->data->ast_command, var_list);
}
/**
static void exec_pipe_builtins(struct ast_node *node)
{
    if (!node)
        return;
    if (node->type == TYPE_PIPE)
        exit(exec_pipe(node->data->ast_pipe->node1,
                       node->data->ast_pipe->node2));
    if (!node->data || !node->data->ast_command
        || !node->data->ast_command->argv || !node->data->ast_command->argv[0])
    {
        printf("ALERTE");
        return;
    }
    if (!strcmp(node->data->ast_command->argv[0], "echo"))
        exit(execute_echo(node->data->ast_command));
    else if (!strcmp(node->data->ast_command->argv[0], "exit"))
    {
        exit_value = execute_exit(node->data->ast_command);
        exit(exit_value);
    }
    else
    {
        node->data->ast_command->argv =
            realloc(node->data->ast_command->argv,
                    sizeof(char *) * (node->data->ast_command->size + 1));
        node->data->ast_command->argv[node->data->ast_command->size] = NULL;
        execvp(node->data->ast_command->argv[0], node->data->ast_command->argv);
    }
}
**/
static int exec_pipe(struct ast_node *left, struct ast_node *right,
                     struct var_list *var_list)
{
    int res;
    int pid;
    int pid2;
    int fds[2];
    if (pipe(fds) == -1)
        errx(1, "Failed to create pipe file descriptors.");

    pid = fork();
    if (pid < 0)
        errx(1, "Failed to fork.");

    if (pid == 0) // child
    {
        close(fds[0]); // close stdout of writer
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]); // close stdin of reader
        res = execute(left, var_list); // exec de left
        exit(res);
        err(127, "failed to execute");
    }
    else // parent
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);
            res = execute(right, var_list); // exec de left
            exit(res);
            err(127, "failed to execute");
        }
        else
        {
            int status;
            close(fds[0]);
            close(fds[1]);
            waitpid(pid, NULL, 0);
            waitpid(pid2, &status, 0);
            fflush(stdout);

            return WEXITSTATUS(status);
        }
    }
    return -1;
}

int execute(struct ast_node *node, struct var_list *var_list)
{
    if (exit_value >= 0 && exit_value <= 260)
        return exit_value;

    if (exit_value >= 300)
        exit_value = -1;

    if (!node)
        return 0;

    int res = 0;
    if (node->type == TYPE_COMMAND)
        res = exec_command(node, var_list);

    else if (node->type == TYPE_IF)
    {
        if (!execute(node->data->ast_if->cond, var_list))
            res = execute(node->data->ast_if->then, var_list);
        else
        {
            if (node->data->ast_if->elif)
                res = execute(node->data->ast_if->elif, var_list);
        }
    }

    if (exit_value >= 301)
        return res;

    else if (node->type == TYPE_WHILE)
    {
        while (exit_value <= 300
               && !execute(node->data->ast_while->wcond, var_list)
               && exit_value <= 300)
        {
            execute(node->data->ast_while->wdo, var_list);
            if (exit_value >= 300)
            {
                exit_value--;
            }
        }
    }
    else if (node->type == TYPE_UNTIL)
    {
        while (exit_value <= 300
               && execute(node->data->ast_until->ucond, var_list)
               && exit_value <= 300)
        {
            execute(node->data->ast_until->udo, var_list);
            if (exit_value >= 300)
                exit_value--;
        }
    }
    else if (node->type == TYPE_ELIF)
    {
        if (!execute(node->data->ast_elif->cond, var_list))
            res = execute(node->data->ast_elif->then, var_list);
        else
        {
            if (node->data->ast_elif->elif)
                return execute(node->data->ast_if->elif, var_list);
        }
    }
    else if (node->type == TYPE_AND)
    {
        res = (!execute(node->data->ast_and->node1, var_list)
               && !execute(node->data->ast_and->node2, var_list));
        res = (!res);
    }
    else if (node->type == TYPE_OR)
    {
        res = (!execute(node->data->ast_and->node1, var_list)
               || !execute(node->data->ast_and->node2, var_list));
        res = (!res);
    }

    else if (node->type == TYPE_PIPE)
    {
        struct ast_node *left = node->data->ast_pipe->node1;
        struct ast_node *right = node->data->ast_pipe->node2;
        res = exec_pipe(left, right, var_list);
    }

    else if (node->type == TYPE_NEG)
        res = !(execute(node->data->ast_neg->node1, var_list));
    else if (node->type == TYPE_FOR)
    {
        for (size_t i = 0; i < node->data->ast_for->size; i++)
        {
            if (exit_value >= 300)
            {
                exit_value--;
                break;
            }
            char *str = calloc(512, 1);
            strcat(strcat(strcat(str, node->data->ast_for->name), "="),
                   node->data->ast_for->word[i]);

            search_var(str, var_list);
            res = execute(node->data->ast_for->fdo, var_list);
            free(str);
        }
    }
    else if (node->type == TYPE_BRACKET)
    {
        struct ast_node *tree = parser(node->data->ast_cb->tok);
        execute(tree, var_list);
        tree_free(tree);
    }
    if (node->next)
        res = execute(node->next, var_list);

    return res;
}
