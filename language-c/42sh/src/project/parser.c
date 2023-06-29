#include "parser.h"

static void identify_type(struct token_list *tokens, size_t *index,
                          struct ast_node *node)
{
    if (tokens->list[*index]->type == TOKEN_IF)
        node->type = TYPE_IF;
    else if (tokens->list[*index]->type == TOKEN_ELIF)
        node->type = TYPE_ELIF;
    else if (tokens->list[*index]->type == TOKEN_WHILE)
        node->type = TYPE_WHILE;
    else if (tokens->list[*index]->type == TOKEN_UNTIL)
        node->type = TYPE_UNTIL;
    else if (tokens->list[*index]->type == TOKEN_WORDS)
        node->type = TYPE_COMMAND;
    else if (tokens->list[*index]->type == TOKEN_AND)
        node->type = TYPE_AND;
    else if (tokens->list[*index]->type == TOKEN_OR)
        node->type = TYPE_OR;
    else if (tokens->list[*index]->type == TOKEN_PIPE)
        node->type = TYPE_PIPE;
    else if (tokens->list[*index]->type == TOKEN_NEG)
        node->type = TYPE_NEG;
    else if (tokens->list[*index]->type == TOKEN_COLON)
        node->type = TYPE_COLON;
    else if (tokens->list[*index]->type == TOKEN_FOR)
        node->type = TYPE_FOR;
    else if (tokens->list[*index]->type == TOKEN_BRACKET_OPEN)
        node->type = TYPE_BRACKET;
    else
        node->type = -1;
}

static struct ast_node *create_pipe_node(struct ast_node *node)
{
    struct ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->next = NULL;
    new_node->data = malloc(sizeof(struct ast_node));
    new_node->type = TYPE_PIPE;
    new_node->data->ast_pipe = malloc(sizeof(struct ast_pipe));
    new_node->data->ast_pipe->node1 = node;
    return new_node;
}

static struct ast_node *create_and_node(struct ast_node *node)
{
    struct ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->next = NULL;
    new_node->data = malloc(sizeof(struct ast_node));
    new_node->type = TYPE_AND;
    new_node->data->ast_and = malloc(sizeof(struct ast_and));
    new_node->data->ast_and->node1 = node;
    return new_node;
}

static struct ast_node *create_or_node(struct ast_node *node)
{
    struct ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->next = NULL;
    new_node->data = malloc(sizeof(struct ast_node));
    new_node->type = TYPE_OR;
    new_node->data->ast_or = malloc(sizeof(struct ast_or));
    new_node->data->ast_or->node1 = node;
    return new_node;
}

static struct ast_elif *create_elif_node(struct token_list *tokens,
                                         size_t *index)
{
    struct ast_elif *node = malloc(sizeof(struct ast_elif));
    node->elif = NULL;
    *index += 1;
    node->cond = create_node(tokens, index, 0);
    *index += 1;
    node->then = create_node(tokens, index, 0);
    if (tokens->list[*index]->type == TOKEN_ELSE
        || tokens->list[*index]->type == TOKEN_ELIF)
    {
        if (tokens->list[*index]->type == TOKEN_ELSE)
            *index += 1;
        node->elif = create_node(tokens, index, 0);
    }
    return node;
}

static struct ast_if *create_if_node(struct token_list *tokens, size_t *index)
{
    struct ast_if *node = malloc(sizeof(struct ast_if));
    node->elif = NULL;
    *index += 1;
    node->cond = create_node(tokens, index, 0);
    *index += 1;
    node->then = create_node(tokens, index, 0);
    if (tokens->list[*index]->type == TOKEN_ELSE
        || tokens->list[*index]->type == TOKEN_ELIF)
    {
        if (tokens->list[*index]->type == TOKEN_ELSE)
            *index += 1;
        node->elif = create_node(tokens, index, 0);
    }
    if (*index < tokens->size && tokens->list[*index]->type == TOKEN_FI)
        *index += 1;
    return node;
}

static struct ast_until *create_until_node(struct token_list *tokens,
                                           size_t *index)
{
    struct ast_until *node = malloc(sizeof(struct ast_until));
    *index += 1;
    node->ucond = create_node(tokens, index, 0);
    *index += 1;
    node->udo = create_node(tokens, index, 0);
    *index += 1;
    return node;
}

static size_t count_cmd(struct token_list *tokens, size_t *index);

static struct ast_for *create_for_node(struct token_list *tokens, size_t *index)
{
    struct ast_for *node = malloc(sizeof(struct ast_for));
    *index += 1;
    node->name = tokens->list[*index]->data;
    *index += 1;
    *index += 1;
    node->word = malloc(sizeof(char *) * 100);
    size_t index_word = 0;
    while (tokens->list[*index]->type != TOKEN_COLON)
    {
        node->word[index_word] = tokens->list[*index]->data;
        *index += 1;
        index_word++;
    }
    *index += 2;
    node->size = index_word;
    node->fdo = create_node(tokens, index, 0);
    *index += 1;
    return node;
}

static size_t count_cmd(struct token_list *tokens, size_t *index)
{
    size_t count = 0;
    size_t new_index = *index;
    while (new_index < tokens->size
           && (tokens->list[new_index]->type == TOKEN_WORDS
               || tokens->list[new_index]->type == TOKEN_REDIR))
    {
        count++;
        new_index++;
    }
    return count;
}

static struct ast_while *create_while_node(struct token_list *tokens,
                                           size_t *index)
{
    struct ast_while *node = malloc(sizeof(struct ast_while));
    *index += 1;
    node->wcond = create_node(tokens, index, 0);
    *index += 1;
    node->wdo = create_node(tokens, index, 0);
    *index += 1;
    return node;
}

static struct ast_command *create_command_node(struct token_list *tokens,
                                               size_t *index)
{
    struct ast_command *node = malloc(sizeof(struct ast_command));
    node->argv = malloc(sizeof(char *) * count_cmd(tokens, index));
    node->size = count_cmd(tokens, index);
    size_t cmd_ind = 0;
    while (*index < tokens->size
           && (tokens->list[*index]->type == TOKEN_WORDS
               || tokens->list[*index]->type == TOKEN_REDIR))
    {
        node->argv[cmd_ind++] = tokens->list[*index]->data;
        *index += 1;
    }
    return node;
}

static struct ast_neg *create_neg_node(struct token_list *tokens, size_t *index)
{
    struct ast_neg *node = malloc(sizeof(struct ast_neg));
    *index += 1;
    node->node1 = create_node(tokens, index, 2);
    return node;
}

static struct ast_cb *create_cb_node(struct token_list *tokens, size_t *index)
{
    struct ast_cb *node = malloc(sizeof(struct ast_cb));
    node->tok = malloc(sizeof(struct token_list));
    node->tok->capacity = tokens->capacity;
    *index += 1;
    node->tok->list = malloc(sizeof(struct token *) * tokens->capacity);
    size_t index_cb = 0;
    while (tokens->list[*index]->type != TOKEN_BRACKET_CLOSE)
    {
        node->tok->list[index_cb] = tokens->list[*index];
        *index += 1;
        index_cb++;
    }
    node->tok->size = index_cb;
    *index += 1;
    return node;
}
struct ast_node *create_node(struct token_list *tokens, size_t *index, int mode)
{
    if (*index >= tokens->size)
        return NULL;
    struct ast_node *node = malloc(sizeof(struct ast_node));
    identify_type(tokens, index, node);
    node->data = malloc(sizeof(struct ast_node));
    node->next = NULL;

    if (node->type == TYPE_COMMAND)
        node->data->ast_command = create_command_node(tokens, index);

    else if (node->type == TYPE_IF)
        node->data->ast_if = create_if_node(tokens, index);

    else if (node->type == TYPE_ELIF)
        node->data->ast_elif = create_elif_node(tokens, index);

    else if (node->type == TYPE_WHILE)
        node->data->ast_while = create_while_node(tokens, index);

    else if (node->type == TYPE_UNTIL)
        node->data->ast_until = create_until_node(tokens, index);

    else if (node->type == TYPE_NEG)
        node->data->ast_neg = create_neg_node(tokens, index);

    else if (node->type == TYPE_FOR)
        node->data->ast_for = create_for_node(tokens, index);

    else if (node->type == TYPE_BRACKET)
        node->data->ast_cb = create_cb_node(tokens, index);

    if (*index >= tokens->size)
        return node;

    if (tokens->list[*index]->type == TOKEN_FI)
        return node;

    if (mode == 1 || *index >= tokens->size)
    {
        return node;
    }
    if (tokens->list[*index]->type == TOKEN_PIPE)
    {
        while (*index < tokens->size
               && tokens->list[*index]->type == TOKEN_PIPE)
        {
            node = create_pipe_node(node);
            *index += 1;
            node->data->ast_pipe->node2 = create_node(tokens, index, 1);
        }
    }

    if (*index >= tokens->size || mode == 2)
    {
        return node;
    }

    if (tokens->list[*index]->type == TOKEN_COLON)
    {
        *index += 1;
        if (*index < tokens->size
            && !(tokens->list[*index]->type == TOKEN_ELIF
                 || tokens->list[*index]->type == TOKEN_ELSE
                 || tokens->list[*index]->type == TOKEN_FI
                 || tokens->list[*index]->type == TOKEN_DO
                 || tokens->list[*index]->type == TOKEN_THEN
                 || tokens->list[*index]->type == TOKEN_DONE))
        {
            node->next = create_node(tokens, index, 0);
        }
        else
        {
            return node;
        }
    }

    else if (tokens->list[*index]->type == TOKEN_OR
             || tokens->list[*index]->type == TOKEN_AND)
    {
        while (*index < tokens->size
               && (tokens->list[*index]->type == TOKEN_OR
                   || tokens->list[*index]->type == TOKEN_AND))
        {
            if (tokens->list[*index]->type == TOKEN_AND)
            {
                node = create_and_node(node);
                *index += 1;
                node->data->ast_and->node2 = create_node(tokens, index, 2);
            }
            else if (tokens->list[*index]->type == TOKEN_OR)
            {
                node = create_or_node(node);
                *index += 1;
                node->data->ast_or->node2 = create_node(tokens, index, 2);
            }
        }
        *index += 1;
        node->next = create_node(tokens, index, 0);
    }

    return node;
}

struct ast_node *parser(struct token_list *tokens)
{
    size_t *index = malloc(sizeof(size_t));
    *index = 0;
    struct ast_node *tree = NULL;
    tree = create_node(tokens, index, 0);
    free(index);
    return tree;
}
