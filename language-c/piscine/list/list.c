#include "list.h"

struct list *list_add(struct list *l, int e)
{
    struct list *new_list = malloc(sizeof(struct list));

    if (!new_list)
        return l;

    new_list->data = e;
    new_list->next = l;
    return new_list;
}

struct list *list_find(struct list *l, int e)
{
    if (!l)
        return NULL;

    struct list *tmp = l;

    while (tmp->next)
    {
        if (tmp->data == e)
            return tmp;
        tmp = tmp->next;
    }

    if (tmp->data == e)
        return tmp;
    return NULL;
}

struct list *list_remove(struct list *l, int e)
{
    if (!l)
        return NULL;

    if (l && l->data == e)
    {
        struct list *tmp = l->next;
        free(l);
        return tmp;
    }

    struct list *tmp = l;
    if (!tmp)
        return l;

    while (tmp->next)
    {
        if (tmp->next->data == e)
        {
            struct list *tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp2);
            return l;
        }
        tmp = tmp->next;
    }
    return l;
}

static struct list *init_list(int e)
{
    struct list *new_list = malloc(sizeof(struct list));
    new_list->data = e;
    new_list->next = NULL;

    return new_list;
}

struct list *list_reverse_sorted_add(struct list *l, int e)
{
    if (!l)
        return init_list(e);

    if (e >= l->data)
    {
        struct list *tmp = malloc(sizeof(struct list));
        if (!tmp)
            return l;
        tmp->data = e;
        tmp->next = l;
        return tmp;
    }

    struct list *tmp = l;
    while (tmp->next)
    {
        if (tmp->next->data <= e)
        {
            struct list *tmp2 = malloc(sizeof(struct list));
            tmp2->data = e;
            tmp2->next = tmp->next;
            tmp->next = tmp2;
            return l;
        }
        tmp = tmp->next;
    }
    struct list *tmp2 = malloc(sizeof(struct list));
    tmp2->data = e;
    tmp2->next = NULL;
    tmp->next = tmp2;
    return l;
}

struct list *list_remove_if(struct list *l, int (*predicate)(int))
{
    if (!l)
        return NULL;

    while (l->next && predicate(l->data))
    {
        struct list *tmp2 = l;
        l = l->next;
        free(tmp2);
    }

    struct list *tmp = l;
    while (tmp->next)
    {
        if (predicate(tmp->next->data) == 1)
        {
            struct list *tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp2);
        }
        else
            tmp = tmp->next;
    }
    if (predicate(tmp->data) == 1)
    {
        free(tmp);
        return NULL;
    }
    return l;
}
