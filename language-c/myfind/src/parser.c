#include "action.h"
#include "expression.h"
#include "myfind.h"

struct stack
{
    struct node *node;
    struct stack *next;
};

static int arg_type(char *s)
{
    if (!strcmp(s, "-o"))
        return 0;
    else if (!strcmp(s, "-a"))
        return 1;
    else if (!strcmp(s, "-print"))
        return 2;
    else if (!strcmp(s, "-name"))
        return 3;
    else if (!strcmp(s, "-type"))
        return 4;
    return -1;
}

static struct stack *push_implicit_and(struct stack *operands)
{
    struct stack *new_stack = malloc(sizeof(struct stack));
    struct node *new_node = malloc(sizeof(struct node));

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->type = 1;
    new_node->value = "-a";

    new_stack->next = operands;
    new_stack->node = new_node;

    return new_stack;
}

static struct stack *stack_push_operands(struct stack *operands, char *argv[],
                                         int index)
{
    struct node *new_operands = malloc(sizeof(struct node));
    new_operands->type = arg_type(argv[index]);
    new_operands->left = NULL;
    new_operands->right = NULL;
    new_operands->value = argv[index + 1];

    struct stack *new_stack = malloc(sizeof(struct stack));
    new_stack->node = new_operands;
    new_stack->next = operands;

    return new_stack;
}

static struct stack *stack_depop(struct stack *operators,
                                 struct stack *operands)
{
    operators->node->left = operands->next->node;
    operators->node->right = operands->node;
    operands->next->node = operators->node;
    operands = operands->next;

    return operands;
}

static struct stack *depop_operators(struct stack *operators, char *name)
{
    struct node *new_operators = malloc(sizeof(struct node));
    new_operators->type = arg_type(name);
    new_operators->right = NULL;
    new_operators->value = name;

    while (operators && operators->node
           && (arg_type(name) < (int)operators->node->type))
        operators = operators->next;

    struct stack *new_stack = malloc(sizeof(struct stack));
    new_stack->node = new_operators;
    new_stack->next = operators;
    return new_stack;
}

static struct stack *stack_push_operators(struct stack *operators,
                                          struct stack *operands, char *name)
{
    while (operators->node && (arg_type(name) < (int)operators->node->type))
    {
        operands = stack_depop(operators, operands);
        operators = operators->next;
    }
    return operands;
}

static struct node *make_ast(struct stack *operators, struct stack *operands)
{
    while (operators->next)
    {
        operators->node->left = operands->next->node;
        operators->node->right = operands->node;

        operands->next->node = operators->node;
        operands = operands->next;

        operators = operators->next;
    }
    return operands->node;
}

int parser(int argc, char *argv[], int index)
{
    struct stack *operators = malloc(sizeof(struct node));
    struct stack *operands = malloc(sizeof(struct node));
    int test = 0;

    while (index < argc)
    {
        if (arg_type(argv[index]) < 0)
        {
            fprintf(stderr, "myfind: Unknown predicate '%s'\n", argv[index]);
            return 1;
        }

        else if (arg_type(argv[index]) > 1)
        {
            if (test == 1)
                operators = push_implicit_and(operators);

            operands = stack_push_operands(operands, argv, index);
            index += 2;
            test = 1;
        }
        else if (arg_type(argv[index]) <= 1)
        {
            operands = stack_push_operators(operators, operands, argv[index]);
            operators = depop_operators(operators, argv[index]);
            if (!operators)
            {
                fprintf(stderr, "myfind: error in expression\n");
                return 1;
            }
            index++;
            test = 0;
        }
    }
    /*
    struct node *ast = make_ast(operators, operands);
    printf("0: %s\n", ast->value);

    printf("1: %d", ast->left->type);
    printf("   %s", ast->left->value);
    printf("        %d", ast->right->type);
    printf("  %s\n", ast->right->value);

    printf("2: %d %s", ast->left->left->type, ast->left->left->value);
    printf("    %d  %s", ast->left->right->type, ast->left->right->value);
    printf("    %d  %s", ast->right->left->type, ast->right->left->value);
    printf("    %d  %s\n", ast->right->right->type, ast->right->right->value);
    */
    return evaluate(make_ast(operators, operands), argc, argv, 2);
}
