#ifndef EXPRESSION_H
#define EXPRESSION_H

enum node_type
{
    OR = 0,
    AND,
    PRINT,
    NAME,
    TYPE,
};

struct node
{
    enum node_type type;
    struct node *left;
    struct node *right;
    char *value;
};

struct function
{
    enum node_type type;
    int (*fun)(int, char **, char *, int);
};

#endif /* ! EXPRESSION_H */
