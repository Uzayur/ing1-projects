#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

struct dlist *dlist_init(void)
{
    struct dlist *dlist = malloc(sizeof(struct dlist));

    dlist->size = 0;
    dlist->head = NULL;
    dlist->tail = NULL;

    return dlist;
}

int dlist_push_front(struct dlist *list, int element)
{
    if (!list || element < 0)
        return 0;

    struct dlist_item *l = malloc(sizeof(struct dlist_item));
    l->data = element;
    l->prev = NULL;

    if (list->size == 0)
    {
        l->next = NULL;
        list->head = l;
        list->tail = l;
    }
    else
    {
        l->next = list->head;
        list->head->prev = l;
        list->head = l;
    }
    list->size += 1;

    return 1;
}

void dlist_print(const struct dlist *list)
{
    if (!list || list->size == 0)
        return;

    struct dlist_item *tmp = list->head;

    while (tmp)
    {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}

int dlist_push_back(struct dlist *list, int element)
{
    if (!list)
        return 0;

    struct dlist_item *l = malloc(sizeof(struct dlist_item));
    l->data = element;
    l->next = NULL;

    if (list->size == 0)
    {
        l->prev = NULL;
        list->head = l;
        list->tail = l;
    }
    else
    {
        l->prev = list->tail;
        list->tail->next = l;
        list->tail = l;
    }
    list->size += 1;
    return 1;
}

size_t dlist_size(const struct dlist *list)
{
    return list->size;
}
