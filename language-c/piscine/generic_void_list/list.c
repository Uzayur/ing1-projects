#include "list.h"

#include <stdlib.h>
#include <string.h>

struct list *list_prepend(struct list *list, const void *value,
                          size_t data_size)
{
    if (data_size > 2147483647)
        return NULL;

    struct list *new_list = malloc(sizeof(struct list));
    new_list->data = malloc(sizeof(value));

    if (!new_list)
        return NULL;

    memcpy(new_list->data, value, data_size);

    new_list->next = list;

    return new_list;
}

size_t list_length(struct list *list)
{
    int size = 0;
    struct list *tmp = list;
    while (tmp)
    {
        size++;
        tmp = tmp->next;
    }

    return size;
}

void list_destroy(struct list *list)
{
    if (!list)
        return;

    free(list->data);
    list_destroy(list->next);
    free(list);
}
