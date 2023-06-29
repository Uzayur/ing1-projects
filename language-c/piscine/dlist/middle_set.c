#include <stdlib.h>

#include "dlist.h"

int dlist_get(struct dlist *list, size_t index)
{
    if (!list || index >= list->size)
        return -1;

    struct dlist_item *tmp = list->head;
    for (size_t i = 0; i < index; i++)
        tmp = tmp->next;

    return tmp->data;
}

int dlist_insert_at(struct dlist *list, int element, size_t index)
{
    if (!list || element < 0 || index > list->size)
        return -1;

    if (index == list->size)
    {
        dlist_push_back(list, element);
        return 1;
    }

    if (index == 0)
    {
        dlist_push_front(list, element);
        return 1;
    }

    struct dlist_item *tmp = list->head;

    for (size_t i = 0; i < index; i++)
        tmp = tmp->next;

    struct dlist_item *l = malloc(sizeof(struct dlist_item));
    l->data = element;
    l->next = tmp;

    if (tmp && tmp->prev)
    {
        l->prev = tmp->prev;
        tmp->prev->next = l;
    }
    tmp->prev = l;

    list->size += 1;

    return 1;
}

int dlist_find(const struct dlist *list, int element)
{
    if (!list || element < 0)
        return -1;

    struct dlist_item *tmp = list->head;

    int index = 0;
    while (tmp)
    {
        if (tmp->data == element)
            return index;
        index++;
        tmp = tmp->next;
    }
    return -1;
}

int dlist_remove_at(struct dlist *list, size_t index)
{
    if (!list || index >= list->size)
        return -1;

    struct dlist_item *tmp = list->head;
    if (index == 0 && list->size == 1)
    {
        list->tail = NULL;
        list->head = NULL;
    }

    else if (index == 0 && list->size != 1)
    {
        list->head = tmp->next;
        tmp->next->prev = NULL;
    }
    else if (index == list->size - 1)
    {
        tmp = list->tail;
        list->tail = tmp->prev;
        tmp->prev->next = NULL;
    }
    else
    {
        for (size_t i = 0; i < index; i++)
            tmp = tmp->next;

        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
    }

    int element = tmp->data;
    free(tmp);

    list->size -= 1;

    return element;
}
