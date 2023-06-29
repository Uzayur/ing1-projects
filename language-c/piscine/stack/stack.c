#include "stack.h"

#include <stddef.h>
#include <stdlib.h>

struct stack *stack_push(struct stack *s, int e)
{
    struct stack *new_stack = malloc(sizeof(struct stack));
    if (!new_stack)
        return s;

    new_stack->data = e;
    new_stack->next = s;
    return new_stack;
}

struct stack *stack_pop(struct stack *s)
{
    if (!s)
        return NULL;

    struct stack *new_stack = s->next;
    free(s);

    return new_stack;
}

int stack_peek(struct stack *s)
{
    return s->data;
}
