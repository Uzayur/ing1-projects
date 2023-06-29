#include "free.h"

#include "expressions.h"

void tree_free(struct ast_node *tree);

static void free_ast_pipe(struct ast_pipe *tree)
{
    tree_free(tree->node1);
    tree_free(tree->node2);
    free(tree);
}

static void free_ast_or(struct ast_or *tree)
{
    tree_free(tree->node1);
    tree_free(tree->node2);
    free(tree);
}

static void free_ast_and(struct ast_and *tree)
{
    tree_free(tree->node1);
    tree_free(tree->node2);
    free(tree);
}

static void free_ast_if(struct ast_if *tree)
{
    tree_free(tree->cond);
    tree_free(tree->then);
    tree_free(tree->elif);
    free(tree);
}

static void free_ast_elif(struct ast_elif *tree)
{
    tree_free(tree->cond);
    tree_free(tree->then);
    tree_free(tree->elif);

    free(tree);
}

static void free_ast_while(struct ast_while *tree)
{
    tree_free(tree->wcond);
    tree_free(tree->wdo);

    free(tree);
}

static void free_ast_until(struct ast_until *tree)
{
    tree_free(tree->ucond);
    tree_free(tree->udo);

    free(tree);
}

static void free_ast_command(struct ast_command *tree)
{
    free(tree->argv);
    free(tree);
}

static void free_ast_neg(struct ast_neg *tree)
{
    tree_free(tree->node1);
    free(tree);
}

static void free_ast_for(struct ast_for *tree)
{
    tree_free(tree->fdo);
    free(tree->word);
    free(tree);
}

static void free_ast_cb(struct ast_cb *tree)
{
    free(tree->tok->list);
    free(tree->tok);
    free(tree);
}

void token_list_free(struct token_list *list)
{
    if (!list)
        return;

    for (int indice_list = list->size - 1; indice_list >= 0; indice_list--)
    {
        free(list->list[indice_list]->data);
        free(list->list[indice_list]);
    }
    free(list->list);
    free(list);
}

void tree_free(struct ast_node *tree)
{
    if (!tree)
        return;

    if (tree->type == TYPE_IF)
        free_ast_if(tree->data->ast_if);

    else if (tree->type == TYPE_ELIF)
        free_ast_elif(tree->data->ast_elif);

    else if (tree->type == TYPE_COMMAND)
        free_ast_command(tree->data->ast_command);

    else if (tree->type == TYPE_AND)
        free_ast_and(tree->data->ast_and);

    else if (tree->type == TYPE_OR)
        free_ast_or(tree->data->ast_or);

    else if (tree->type == TYPE_PIPE)
        free_ast_pipe(tree->data->ast_pipe);

    else if (tree->type == TYPE_UNTIL)
        free_ast_until(tree->data->ast_until);

    else if (tree->type == TYPE_WHILE)
        free_ast_while(tree->data->ast_while);

    else if (tree->type == TYPE_NEG)
        free_ast_neg(tree->data->ast_neg);

    else if (tree->type == TYPE_FOR)
        free_ast_for(tree->data->ast_for);

    else if (tree->type == TYPE_BRACKET)
        free_ast_cb(tree->data->ast_cb);

    tree_free(tree->next);

    free(tree->data);
    free(tree);
}

void var_list_free(struct var_list *list)
{
    for (size_t indice = 0; indice < list->size; indice++)
    {
        free(list->list[indice]->name);
        for (size_t j = 0; j < list->list[indice]->size; j++)
        {
            free(list->list[indice]->value[j]);
        }
        free(list->list[indice]->value);
        free(list->list[indice]);
    }

    free(list->list);
    free(list);
}
