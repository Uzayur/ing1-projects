#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "expression.h"

int eval_expr(struct my_expr *expr)
{
    if (expr->type == 4)
        return -expr->data.children.left->data.value;

    if (expr->type == 5)
        return expr->data.value;

    else
    {
        int result = 0;
        struct my_expr *left = expr->data.children.left;
        struct my_expr *right = expr->data.children.right;
        int type = expr->type;

        if (type == 0)
            result = eval_expr(left) + eval_expr(right);

        else if (type == 1)
            result = eval_expr(left) - eval_expr(right);

        else if (type == 2)
            result = eval_expr(left) * eval_expr(right);

        else if (type == 3)
        {
            if (eval_expr(right) == 0)
            {
                fprintf(stderr, "student: Division by zero not allowed!\n");
                exit(1);
            }
            result = eval_expr(left) / eval_expr(right);
        }
        return result;
    }
}
