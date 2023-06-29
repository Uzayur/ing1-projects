#include "gtree.h"

#include <stdio.h>
#include <stdlib.h>

struct gtree *gtree_create_node(char data)
{
    struct gtree *node = malloc(sizeof(struct gtree));

    if (!node)
        return NULL;

    node->data = data;
    node->children = NULL;
    node->siblings = NULL;

    return node;
}

int gtree_add_child(struct gtree *parent, struct gtree *child)
{
    if (!parent || !child)
        return 0;

    if (!parent->children)
        parent->children = child;
    else
    {
        struct gtree *tmp = parent->children;
        while (tmp)
        {
            if (!tmp->siblings)
            {
                tmp->siblings = child;
                return 1;
            }
            tmp = tmp->siblings;
        }
    }
    return 1;
}

struct gtree *gtree_search_node(struct gtree *root, char data)
{
    if (!root)
        return NULL;

    if (root->data == data)
        return root;

    struct gtree *tmp = NULL;
    if (root->siblings)
        tmp = gtree_search_node(root->siblings, data);
    if (!tmp)
        tmp = gtree_search_node(root->children, data);
    return tmp;
}

void gtree_free(struct gtree *root)
{
    if (!root)
        return;

    gtree_free(root->children);
    gtree_free(root->siblings);
    free(root);
}

static struct gtree *gtree_delete(struct gtree *root, char data)
{
    if (!root)
        return NULL;

    if (root->data == data)
    {
        gtree_free(root->children);
        struct gtree *node = root->siblings;
        free(root);
        return node;
    }
    else
    {
        root->children = gtree_delete(root->children, data);
        root->siblings = gtree_delete(root->siblings, data);
    }
    return root;
}

int gtree_del_node(struct gtree *root, char data)
{
    if (!root || !gtree_search_node(root, data))
        return 0;

    if (root->data == data)
        return -1;

    gtree_delete(root, data);
    return 1;
}
