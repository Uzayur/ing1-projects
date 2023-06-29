#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

void dlist_map_square(struct dlist *list)
{
    if (!list || list->size == 0)
        return;

    struct dlist_item *tmp = list->head;

    while (tmp)
    {
        tmp->data *= tmp->data;
        tmp = tmp->next;
    }
}

static void dlist_reverse_arg(struct dlist_item *head, struct dlist_item *tail,
                              size_t begin, size_t end)
{
    if (begin > end)
        return;
    else
    {
        int tmp = head->data;
        head->data = tail->data;
        tail->data = tmp;

        begin++;
        end--;

        dlist_reverse_arg(head->next, tail->prev, begin, end);
    }
}

void dlist_reverse(struct dlist *list)
{
    if (!list || list->size < 2)
        return;

    size_t end = list->size - 1;
    size_t begin = 0;

    dlist_reverse_arg(list->head, list->tail, begin, end);
}

struct dlist *dlist_split_at(struct dlist *list, size_t index)
{
    if (!list)
        return dlist_init();

    if (index >= list->size)
        return NULL;

    struct dlist *l2 = dlist_init();
    struct dlist_item *tmp = list->tail;

    for (size_t i = list->size; i > index; i--)
    {
        dlist_push_front(l2, tmp->data);
        tmp = tmp->prev;
        dlist_remove_at(list, i);
    }
    dlist_remove_at(list, index);

    if (list->head)
    {
        tmp = list->head;
        for (size_t i = 0; i < index - 1; i++)
            tmp = tmp->next;

        tmp->next = NULL;
    }

    list->size = index;

    return l2;
}

void dlist_concat(struct dlist *list1, struct dlist *list2)
{
    if (!list1 || !list2 || list2->size == 0)
        return;

    struct dlist_item *tmp = list2->head;
    int index = -1;

    while (tmp)
    {
        dlist_push_back(list1, tmp->data);
        tmp = tmp->next;
        dlist_remove_at(list2, index);
        index++;
    }
    free(list2->head);
    list2->head = NULL;
    list2->tail = NULL;

    list2->size = 0;
}
