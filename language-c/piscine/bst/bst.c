#include "bst.h"

#include <stddef.h>
#include <stdlib.h>

struct bst_node *create_node(int value)
{
    struct bst_node *node = malloc(sizeof(struct bst_node));

    node->data = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct bst_node *add_node(struct bst_node *tree, int value)
{
    if (!tree)
        return create_node(value);
    else if (tree->data < value)
        tree->right = add_node(tree->right, value);
    else if (tree->data > value)
        tree->left = add_node(tree->left, value);
    return tree;
}

static int max_bst(struct bst_node *tree)
{
    if (!tree->right)
        return tree->data;
    else
        return max_bst(tree->right);
}

struct bst_node *delete_node(struct bst_node *tree, int value)
{
    if (!tree)
        return NULL;

    if (tree->data > value)
        tree->left = delete_node(tree->left, value);

    else if (tree->data < value)
        tree->right = delete_node(tree->right, value);

    else
    {
        if (!tree->left && !tree->right)
        {
            free(tree);
            return NULL;
        }
        else if (!tree->left)
        {
            struct bst_node *tmp = tree;
            tree = tree->right;
            free(tmp);
        }
        else if (!tree->right)
        {
            struct bst_node *tmp = tree;
            tree = tree->left;
            free(tmp);
        }
        else
        {
            int max = max_bst(tree->left);
            tree->data = max;
            tree->left = delete_node(tree->left, max);
        }
    }
    return tree;
}

const struct bst_node *find(const struct bst_node *tree, int value)
{
    if (!tree)
        return NULL;
    else
    {
        if (tree->data == value)
            return tree;
        if (tree->data > value)
            return find(tree->left, value);
        if (tree->data < value)
            return find(tree->right, value);
    }
    return NULL;
}

void free_bst(struct bst_node *tree)
{
    if (!tree)
        return;

    free_bst(tree->left);
    free_bst(tree->right);

    free(tree);
}
