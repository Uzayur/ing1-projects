#include "malloc.h"

struct data_head *head = NULL;

static void *initialize_head(struct data_head *head)
{
    // initialize an head after the last one
    struct data_head *new_head = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (!new_head)
        return NULL;

    new_head->size = 4096 - sizeof(struct data_head);
    new_head->data = NULL;
    new_head->next = NULL;

    head->next = new_head;
    return head;
}

static void *search_right_head(size_t size)
{
    // search the right head to insert our data
    struct data_head *tmp = head;
    while (tmp->size - sizeof(struct data_list) < size && tmp->next)
        tmp = tmp->next;

    if (tmp->size - sizeof(struct data_list) >= size)
        return add_data(size, tmp);

    else
    {
        if (!initialize_head(tmp))
            return NULL;
        return add_data(size, tmp->next);
    }
}

static void *reach_max_size(size_t size)
{
    // place a new head with the right size
    struct data_head *tmp = head;

    while (tmp->next)
        tmp = tmp->next;

    int multiple = 1 + size / 4096;
    struct data_head *new_head =
        mmap(NULL, 4096 * multiple, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!new_head)
        return NULL;
    new_head->next = NULL;
    new_head->size = 4096 * multiple - size - sizeof(struct data_head)
        - sizeof(struct data_list);

    struct data_list *new_data = (struct data_list *)new_head + 1;
    new_data->free = 0;
    new_data->size = size;
    new_data->previous = NULL;
    new_data->next = NULL;

    new_head->data = new_data;
    head->next = new_head;

    return new_data;
}

__attribute__((visibility("default"))) void *malloc(size_t size)
{
    // malloc
    if (!head)
    {
        head = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        if (!head)
            return NULL;

        head->size = 4096 - sizeof(struct data_head);
        head->data = NULL;
        head->next = NULL;
        return search_right_head(size);
    }
    if (size > 4096 - sizeof(struct data_head) - sizeof(struct data_list))
        return reach_max_size(size);

    return search_right_head(size);
}

__attribute__((visibility("default"))) void free(void *ptr)
{
    struct data_list *tmp = (struct data_list *)ptr;
    int free_size = tmp->size;

    if (tmp->next && tmp->next->free)
    {
        tmp->size = tmp->size + tmp->next->size;
        tmp->free = 1;
        if (tmp->next->next)
            tmp->next = tmp->next->next;
        else
            tmp->next = NULL;
    }
    else
        tmp->free = 1;

    head->size += free_size;
}

__attribute__((visibility("default"))) void *realloc(void *ptr, size_t size)
{
    if (!ptr)
        return malloc(size);
    else if (size == 0 && ptr)
    {
        free(ptr);
        return NULL;
    }
    free(ptr);
    return NULL;
}

__attribute__((visibility("default"))) void *calloc(size_t nmemb, size_t size)
{
    if (size == 0 || nmemb == 0)
        return NULL;

    size_t beware_overflow = 0;
    if (__builtin_mul_overflow(nmemb, size, &beware_overflow))
        return NULL;

    int *ptr = malloc(size * nmemb);

    if (!ptr)
        return NULL;

    for (size_t i = 0; i < nmemb * size; i += size)
        *(ptr + i) = 0;

    return ptr;
}
