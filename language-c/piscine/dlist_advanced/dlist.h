#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

struct dlist
{
    size_t size;
    struct dlist_item *head;
    struct dlist_item *tail;
};

struct dlist_item
{
    int data;
    struct dlist_item *next;
    struct dlist_item *prev;
};

void dlist_clear(struct dlist *list);
void dlist_shift(struct dlist *list, int offset);
int dlist_add_sort(struct dlist *list, int element);
int dlist_remove_eq(struct dlist *list, int element);
struct dlist *dlist_copy(const struct dlist *list);

void dlist_sort(struct dlist *list);
void dlist_merge(struct dlist *list1, struct dlist *list2);

unsigned int dlist_levenshtein(struct dlist *list1, struct dlist *list2);

#endif
