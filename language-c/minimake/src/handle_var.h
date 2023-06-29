#ifndef HANDLE_VAR_H
#define HANDLE_VAR_H

struct variables
{
    char *name;
    char *value;
    struct variables *next;
};

struct variables *handle_var(char *buffer, struct variables *all_var);

#endif
