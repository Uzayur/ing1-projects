#include "handle_command.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int my_strlen(char *cmd, int begin)
{
    int size = begin;
    while (cmd[size] != '\n' && cmd[size] != '\0')
        size++;
    return size;
}

static int right_size(char *line, int index)
{
	int size = index;
	while (line[size] != ' ' && line[size] != '\t' && line[size] != '\0')
		size++;
	return size;
}

static char *nam(char *line)
{
	int index = 0;
	while (line[index] == ' ' || line[index] == '\t')
		index++;

	char *tmp = malloc(sizeof(char) * right_size(line, index));
	int end = right_size(line, index);
	int tmp_ind = 0;
	while (index != end)
	{
		tmp[tmp_ind] = line[index];
		tmp_ind++;
		index++;
	}
	return tmp;
}

static void execute_line(char *line)
{
	int pid = fork();
	if (pid == 0)
		execlp("/bin/sh", "line", "-c", line);

	int wstatus;
	waitpid(pid, &wstatus, 0);
	int test = WEXITSTATUS(wstatus);
	test++;
}

static int exec_rule_no_dep(char **cmd, int size)
{
    for (int ind = 0; ind < size; ind++)
	{
		int cmd_ind = 0;
		while (cmd[ind][cmd_ind] == ' ' || cmd[ind][cmd_ind] == '\t')
			cmd_ind++;

		char *exec_str = malloc(sizeof(char) * my_strlen(cmd[ind], ind));
		if (cmd[ind][cmd_ind] != '@')
		{
			int str_ind = 0;
			while (cmd[ind][cmd_ind] != '\n' && cmd[ind][cmd_ind] != '\0')
			{
				exec_str[str_ind] = cmd[ind][cmd_ind];
				printf("%c", cmd[ind][cmd_ind]);
				cmd_ind++;
				str_ind++;
			}
			printf("\n");
		}
		else
		{
			cmd_ind++;
			int str_ind = 0;
			while (cmd[ind][cmd_ind] != '\n' && cmd[ind][cmd_ind] != '\0')
			{
				exec_str[str_ind] = cmd[ind][cmd_ind];
				cmd_ind++;
				str_ind++;
			}
		}
		execute_line(exec_str);
	}
	return 0;
}

static void exec_first_rule(struct rules *all_rule)
{
    if (!all_rule)
	{
		printf("minimake: *** No targets. Stop.\n");
		return ;
	}

	struct rules *tmp = malloc(sizeof(struct rules));
    tmp = all_rule;
    while (tmp->next)
        tmp = tmp->next;

    char *name = nam(tmp->target);
	if ((!tmp->command) && (tmp->dep[0][0] == '\n'))
		printf("minimake: Nothing to be done for '%s'.\n", name);

	else if ((tmp->dep[0][0] != '\n') && (!tmp->command))
		exec_rule_no_dep(tmp->command->command_list, tmp->command->size);
}

void handle_command_exec(struct rules *all_rule, struct save *all_arg)
{
    all_arg->argc++;
    exec_first_rule(all_rule);
}
