#include "serialize.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gtree.h"

static void write_in(FILE *file, struct gtree *root)
{
    if (!root)
        return;

    if (root->children)
    {
        fprintf(file, "%c -> %c;\n", root->data, root->children->data);

        struct gtree *tmp = root->children->siblings;
        while (tmp)
        {
            fprintf(file, "%c -> %c;\n", root->data, tmp->data);
            tmp = tmp->siblings;
        }

        write_in(file, root->children);

        tmp = root->children->siblings;
        while (tmp)
        {
            write_in(file, tmp);
            tmp = tmp->siblings;
        }
    }
}

static int one_write(FILE *file, char data)
{
    fprintf(file, "digraph tree {\n");
    fprintf(file, "%c;\n", data);
    fprintf(file, "}\n");

    fclose(file);
    return 0;
}

int gtree_serialize(const char *filename, struct gtree *root)
{
    FILE *file = fopen(filename, "w");

    if (!file)
        return -1;

    if (root && !root->children && !root->siblings)
        return one_write(file, root->data);

    fprintf(file, "digraph tree {\n");
    write_in(file, root);
    fprintf(file, "}\n");

    fclose(file);
    return 0;
}

static int my_strcmp(const char *s1, const char *s2)
{
    int indice = 0;
    while (s1[indice] != '\0')
    {
        if (s1[indice] < s2[indice])
            return -42;
        else if (s1[indice] > s2[indice])
            return 42;
        indice++;
    }
    if (s2[indice] != '\0')
        return -42;
    return 0;
}

static int one_node(char *buffer)
{
    int count = 0;
    int index = 0;
    while (buffer[index] != ';')
    {
        if (buffer[index++] == '-')
            count++;
    }
    return count;
}

static struct gtree *create_tree(FILE *file, char *buffer,
                                 struct gtree *current, struct gtree *tree)
{
    if (!my_strcmp(buffer, "}\n"))
        return tree;

    else if (!one_node(buffer))
    {
        char data = buffer[0];
        return gtree_create_node(data);
    }

    struct gtree *child = gtree_create_node(buffer[5]);
    if (!tree)
    {
        struct gtree *new_current = gtree_create_node(buffer[0]);
        gtree_add_child(new_current, child);
        fgets(buffer, 50, file);
        return create_tree(file, buffer, new_current, new_current);
    }
    else
    {
        if (current->data == buffer[0])
            gtree_add_child(current, child);
        else
        {
            struct gtree *new_current = gtree_search_node(tree, buffer[0]);
            gtree_add_child(new_current, child);
            fgets(buffer, 50, file);
            return create_tree(file, buffer, new_current, tree);
        }
        fgets(buffer, 50, file);
        return create_tree(file, buffer, current, tree);
    }
}

struct gtree *gtree_deserialize(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
        return NULL;

    char *buffer = malloc(sizeof(char) * 50);
    fgets(buffer, 50, file);
    fgets(buffer, 50, file);

    struct gtree *tree = NULL;
    if (!my_strcmp(buffer, "}\n"))
    {
        free(buffer);
        return NULL;
    }
    if (!one_node(buffer))
    {
        char data = buffer[0];
        free(buffer);
        return gtree_create_node(data);
    }

    tree = create_tree(file, buffer, tree, tree);
    free(buffer);
    return tree;
}
