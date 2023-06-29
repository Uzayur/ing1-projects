#include "fifo.h"

#include <stdio.h>
#include <stdlib.h>

struct fifo *fifo_init(void)
{
    struct fifo *f = malloc(sizeof(struct fifo));
    f->head = NULL;
    f->tail = NULL;
    f->size = 0;

    return f;
}

size_t fifo_size(struct fifo *fifo)
{
    return fifo->size;
}

void fifo_push(struct fifo *fifo, int elt)
{
    struct list *l = malloc(sizeof(struct list));
    l->data = elt;
    fifo->size += 1;
    l->next = NULL;

    if (!fifo->head)
    {
        fifo->head = l;
        fifo->tail = l;
    }
    else
    {
        fifo->tail->next = l;
        fifo->tail = l;
    }
}

int fifo_head(struct fifo *fifo)
{
    return fifo->head->data;
}

void fifo_pop(struct fifo *fifo)
{
    if (!fifo || fifo->size == 0)
        return;

    struct list *tmp = fifo->head;
    fifo->head = tmp->next;
    free(tmp);

    fifo->size -= 1;
}

static void free_list(struct list *list)
{
    if (list)
        free_list(list->next);
    free(list);
}

void fifo_clear(struct fifo *fifo)
{
    if (!fifo || fifo->size == 0)
        return;

    free_list(fifo->head);
    fifo->head = NULL;
    fifo->tail = NULL;

    fifo->size = 0;
}

void fifo_destroy(struct fifo *fifo)
{
    free_list(fifo->head);
    free(fifo);
}

void fifo_print(const struct fifo *fifo)
{
    if (!fifo)
        return;

    if (fifo->size == 0)
        return;

    struct list *tmp = fifo->head;
    while (tmp)
    {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}
