#include "malloc.h"

static void allocate_data(size_t size, struct data_head *head)
{
    // allocate a new data with head->data = NULL

    int multiple = 1 + size / sizeof(struct data_list);
    struct data_list *new_data_list = (struct data_list *)head + multiple;

    head->size = head->size - size - sizeof(struct data_list);

    new_data_list->free = 0;
    new_data_list->size = size;
    new_data_list->previous = NULL;
    new_data_list->next = NULL;

    head->data = new_data_list;
}

static void *split_data_block(size_t new_size, struct data_list *data,
                              struct data_head *head)
{
    // split data block
    int multiple = 1 + data->size / sizeof(struct data_list);
    struct data_list *new_data = (struct data_list *)data + multiple;
    new_data->size = new_size;
    new_data->free = 0;

    if (!data->previous)
    {
        new_data->previous = NULL;
        new_data->next = data;
        head->data = new_data;
        data->next = NULL;
    }
    else
    {
        new_data->next = data;
        new_data->previous = data->previous;
    }

    data->size -= new_size;

    return new_data;
}

static void *add_data_list_end(size_t new_size, struct data_head *head)
{
    // allocate a new data at the end
    head->size = head->size - new_size - sizeof(struct data_list);

    struct data_list *tmp = head->data;

    while (tmp->next)
        tmp = tmp->next;

    int multiple = 1 + new_size / sizeof(struct data_list);
    struct data_list *new_data_list = tmp + multiple;

    new_data_list->size = new_size;
    new_data_list->free = 0;
    new_data_list->next = NULL;
    new_data_list->previous = tmp;
    tmp->next = new_data_list;
    return new_data_list;
}

void *add_data(size_t size, struct data_head *head)
{
    if (!head->data)
    {
        allocate_data(size, head);
        return (void *)head->data;
    }

    struct data_list *tmp = head->data;
    while (tmp)
    {
        if (tmp->free && size < tmp->size - sizeof(struct data_list))
        {
            tmp = split_data_block(size, tmp, head);
            head->size = head->size - size - sizeof(struct data_list);
            return tmp;
        }
        tmp = tmp->next;
    }
    return add_data_list_end(size, head);
}
