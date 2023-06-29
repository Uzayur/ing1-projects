#include "pretty_print.h"

static void pretty_tree(struct ast_node *tree);

static void pretty_print_command(struct ast_command *node)
{
    for (size_t index = 0; index < node->size; index++)
    {
        printf(" %s ", node->argv[index]);
    }
    printf("\n");
}

static void pretty_print_if(struct ast_if *ast_if)
{
    printf("if: ");
    pretty_tree(ast_if->cond);

    if (ast_if->then)
    {
        printf("then: ");

        pretty_tree(ast_if->then);
    }

    if (ast_if->elif)
    {
        printf("else ");
        pretty_tree(ast_if->elif);
    }
    printf("fi\n");
}

static void pretty_print_elif(struct ast_elif *ast_if)
{
    printf("if: ");
    pretty_tree(ast_if->cond);
    if (ast_if->then)
    {
        printf("then: ");
        pretty_tree(ast_if->then);
    }
    if (ast_if->elif)
    {
        printf("else ");
        pretty_tree(ast_if->elif);
    }
}

static void pretty_print_neg(struct ast_neg *node)
{
    printf("! ");
    pretty_tree(node->node1);
}

static void pretty_print_until(struct ast_until *node)
{
    printf("until: ");
    pretty_tree(node->ucond);
    printf("do: ");
    pretty_tree(node->udo);
    printf("done:\n");
}

static void pretty_print_while(struct ast_while *node)
{
    printf("while: ");
    pretty_tree(node->wcond);
    printf("do: ");
    pretty_tree(node->wdo);
    printf("done:\n");
}

static void pretty_print_and(struct ast_and *node)
{
    pretty_tree(node->node1);
    printf(" && ");
    pretty_tree(node->node2);
}

static void pretty_print_or(struct ast_or *node)
{
    pretty_tree(node->node1);
    printf(" || ");
    pretty_tree(node->node2);
}

static void pretty_print_pipe(struct ast_pipe *node)
{
    pretty_tree(node->node1);
    printf(" | ");
    pretty_tree(node->node2);
}

static void pretty_print_for(struct ast_for *node)
{
    printf("for %s in ", node->name);
    for (size_t i = 0; i < node->size; i++)
        printf("%s ", node->word[i]);
    printf(" do:  ");
    pretty_tree(node->fdo);
    printf("done:\n");
}

static void pretty_print_cb(struct ast_cb *tree)
{
    printf("{ ");
    for (size_t i = 0; i < tree->tok->size; i++)
        printf("%s ", tree->tok->list[i]->data);
    printf("} ");
}

static void pretty_tree(struct ast_node *tree)
{
    if (tree->type == TYPE_IF)
        pretty_print_if(tree->data->ast_if);

    else if (tree->type == TYPE_ELIF)
        pretty_print_elif(tree->data->ast_elif);

    else if (tree->type == TYPE_COMMAND)
        pretty_print_command(tree->data->ast_command);

    else if (tree->type == TYPE_AND)
        pretty_print_and(tree->data->ast_and);

    else if (tree->type == TYPE_OR)
        pretty_print_or(tree->data->ast_or);

    else if (tree->type == TYPE_PIPE)
        pretty_print_pipe(tree->data->ast_pipe);

    else if (tree->type == TYPE_UNTIL)
        pretty_print_until(tree->data->ast_until);

    else if (tree->type == TYPE_WHILE)
        pretty_print_while(tree->data->ast_while);

    else if (tree->type == TYPE_NEG)
        pretty_print_neg(tree->data->ast_neg);

    else if (tree->type == TYPE_FOR)
        pretty_print_for(tree->data->ast_for);

    else if (tree->type == TYPE_BRACKET)
        pretty_print_cb(tree->data->ast_cb);
    if (tree->next)
    {
        pretty_tree(tree->next);
    }
}

void pretty_print_var(struct var_list *var)
{
    printf("\n##### VAR #####\n");

    for (size_t i = 0; i < var->size; i++)
    {
        printf("%s:", var->list[i]->name);
        for (size_t j = 0; j < var->list[i]->size; j++)
        {
            printf(" %s |", var->list[i]->value[j]);
        }
        printf("\n");
    }
}

void pretty_print(struct ast_node *tree, struct token_list *tokens,
                  struct var_list *var)
{
    printf("##### TOKENS #####\n");
    for (size_t i = 0; i < tokens->size; i++)
        printf("%d: %s\n", tokens->list[i]->type, tokens->list[i]->data);

    printf("\n##### AST #####\n");

    pretty_tree(tree);
    pretty_print_var(var);

    printf("\n#####  EXECUTION #####\n");
}
