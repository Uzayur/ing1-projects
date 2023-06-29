#include "handle_stack.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "handle_rule.h"
#include "handle_var.h"

struct variables *stack_push_var(struct variables *s, char *names, char *val)
{
    if (!s)
    {
        s = malloc(sizeof(struct variables));
        s->name = names;
        s->value = val;
        s->next = NULL;
        return s;
    }

    struct variables *new_s = malloc(sizeof(struct variables));
    if (!new_s)
        return s;

    new_s->name = names;
    new_s->value = val;
    new_s->next = s;

    return new_s;
}

struct rules *stack_push_rule(struct rules *s, char *name, char **dep_list)
{
    if (!s)
    {
        s = malloc(sizeof(struct rules));
        s->target = name;
        s->dep = dep_list;
        s->command = NULL;
        s->next = NULL;
        return s;
    }

    struct rules *new_s = malloc(sizeof(struct rules));
    if (!new_s)
        return s;

    new_s->target = name;
    new_s->dep = dep_list;
    new_s->command = NULL;
    new_s->next = s;

    return new_s;
}
