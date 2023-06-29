#include "dlist.h"
#include "dlist_basics.h"

void dlist_sort(struct dlist *list)
{
    if (!list || list->size == 0)
        return;

    size_t indicator = 0;
    while (indicator != list->size - 1)
    {
        indicator = 0;
        struct dlist_item *tmp = list->head;
        for (size_t i = 0; i < list->size - 1; i++)
        {
            if (tmp->data > tmp->next->data)
            {
                int transition = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = transition;
            }
            else
                indicator++;
            tmp = tmp->next;
        }
    }
}

void dlist_merge(struct dlist *list1, struct dlist *list2)
{
    dlist_concat(list1, list2);
    dlist_sort(list1);
    dlist_clear(list2);
}
