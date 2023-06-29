#include "dlist.h"
#include "dlist_basics.h"

static void dlist_item_clear(struct dlist_item *l)
{
    if (!l)
        return;
    dlist_item_clear(l->next);
    free(l);
}

void dlist_clear(struct dlist *list)
{
    dlist_item_clear(list->head);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void dlist_shift(struct dlist *list, int offset)
{
    if (!list || offset == 0)
        return;

    if (offset > 0)
    {
        int modulo = offset % list->size;
        for (int i = 0; i < modulo; ++i)
        {
            dlist_push_front(list, list->tail->data);
            dlist_remove_at(list, list->size - 1);
        }
    }
    else
    {
        int modulo = (-1 * offset) % list->size;
        for (int i = 0; i < modulo; ++i)
        {
            dlist_push_back(list, list->head->data);
            dlist_remove_at(list, 0);
        }
    }
}

int dlist_add_sort(struct dlist *list, int element)
{
    if (!list || element < 0)
        return -1;

    int index = 0;
    struct dlist_item *tmp = list->head;

    while (tmp)
    {
        if (tmp->data > element)
        {
            dlist_insert_at(list, element, index);
            return 1;
        }
        tmp = tmp->next;
        index++;
    }
    dlist_push_back(list, element);
    return 1;
}

int dlist_remove_eq(struct dlist *list, int element)
{
    if (!list || element < 0)
        return 0;

    int index = 0;
    struct dlist_item *tmp = list->head;
    while (tmp)
    {
        if (tmp->data == element)
        {
            dlist_remove_at(list, index);
            return 1;
        }
        tmp = tmp->next;
        index++;
    }
    return 0;
}

struct dlist *dlist_copy(const struct dlist *list)
{
    if (!list)
        return NULL;

    struct dlist *copy = dlist_init();

    struct dlist_item *tmp = list->head;

    while (tmp)
    {
        dlist_push_back(copy, tmp->data);
        tmp = tmp->next;
    }
    return copy;
}
