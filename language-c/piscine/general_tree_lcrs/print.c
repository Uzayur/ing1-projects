#include "print.h"

#include <stdio.h>
#include <stdlib.h>

static void print_preorder(struct gtree *root)
{
    if (!root)
        return;

    fprintf(stdout, " %c", root->data);
    print_preorder(root->children);
    print_preorder(root->siblings);
}

void gtree_print_preorder(struct gtree *root)
{
    if (!root)
        return;

    fprintf(stdout, "%c", root->data);
    print_preorder(root->children);
    fprintf(stdout, "\n");
}
