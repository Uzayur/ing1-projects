#include "bst_static.h"

#include <stdlib.h>

struct bst *init(size_t capacity)
{
    struct bst *bst = malloc(sizeof(struct bst));

    bst->capacity = capacity;
    bst->size = 0;
    bst->data = malloc(sizeof(struct value *) * capacity);

    for (size_t i = 0; i < bst->capacity; i++)
        bst->data[i] = NULL;

    return bst;
}

static struct value *create_node(int value)
{
    struct value *new_val = malloc(sizeof(struct value));
    new_val->val = value;
    return new_val;
}

void add(struct bst *tree, int value)
{
    size_t index = 0;
    while (index < tree->capacity)
    {
        if (!tree->data[index])
        {
            tree->data[index] = create_node(value);
            tree->size++;
            return;
        }
        if (value > tree->data[index]->val)
            index = 2 * index + 2;
        else if (value < tree->data[index]->val)
            index = 2 * index + 1;
    }

    size_t prev_size = tree->capacity;
    tree->data = realloc(tree->data, (index + 1) * sizeof(struct value *));

    tree->capacity = index + 1;
    for (size_t i = prev_size; i < tree->capacity; i++)
        tree->data[i] = NULL;

    tree->data[index] = create_node(value);
    tree->size++;
}

int search(struct bst *tree, int value)
{
    size_t index = 0;

    while (index < tree->capacity)
    {
        if (value == tree->data[index]->val)
            return index;

        else if (value < tree->data[index]->val)
            index = 2 * index + 1;

        else
            index = 2 * index + 2;
    }
    return -1;
}

void bst_free(struct bst *tree)
{
    if (!tree)
        return;

    int index = 0;
    while (tree->capacity != 0)
    {
        free(tree->data[index]);
        tree->capacity--;
        index++;
    }
    free(tree->data);
    free(tree);
}
