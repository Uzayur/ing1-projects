#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdlib.h>

struct list
{
    int data;
    struct list *next;
};

void list_print(struct list *l);

#endif
