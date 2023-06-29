#ifndef HANDLE_RULE_H
#define HANDLE_RULE_H

struct save
{
    int argc;
    char **argv;
    char *filename;
};

struct commands
{
    int size;
    char **command_list;
};

struct rules
{
    char *target;
    char **dep;
    struct commands *command;
    struct rules *next;
};

struct rules *handle_rule(char *buffer, struct rules *all_rule);
struct commands *handle_command(char *buffer, struct commands *command);

#endif
