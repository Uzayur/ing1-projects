#include "grammar.h"

static int if_check(struct token_list *tokens, size_t *index);
static int for_check(struct token_list *tokens, size_t *index);
static int compound_list_check(struct token_list *tokens, size_t *index);
static int while_check(struct token_list *tokens, size_t *index);

static int words_list_check(struct token_list *tokens, size_t *index)
{
    while (*index < tokens->size && tokens->list[*index]->type != TOKEN_COLON
           && tokens->list[*index]->type != TOKEN_AND
           && tokens->list[*index]->type != TOKEN_OR
           && tokens->list[*index]->type != TOKEN_PIPE)
    {
        if (tokens->list[*index]->type != TOKEN_WORDS
            && tokens->list[*index]->type != TOKEN_NEG
            && tokens->list[*index]->type != TOKEN_REDIR)
            errx(2, "grammar error in words list");
        *index += 1;
    }

    if (*index >= tokens->size && tokens->list[*index - 1]->type != TOKEN_REDIR)
        return 1;
    else if (*index >= tokens->size)
        errx(2, "grammar error: end of file unexpected");

    if (*index < tokens->size
        && (tokens->list[*index]->type == TOKEN_COLON
            || tokens->list[*index]->type == TOKEN_AND
            || tokens->list[*index]->type == TOKEN_OR
            || tokens->list[*index]->type == TOKEN_PIPE))
    {
        *index += 1;

        if (tokens->list[*index - 1]->type == TOKEN_AND
            || tokens->list[*index - 1]->type == TOKEN_OR
            || tokens->list[*index - 1]->type == TOKEN_PIPE)
        {
            if (*index >= tokens->size)
                errx(2, "grammar error: expected something after && || |");
        }
        if (*index < tokens->size
            && (tokens->list[*index]->type == TOKEN_COLON
                || tokens->list[*index]->type == TOKEN_AND
                || tokens->list[*index]->type == TOKEN_OR
                || tokens->list[*index]->type == TOKEN_PIPE))
            errx(2, "grammar error in command/condition");
    }
    return 1;
}

static int else_check(struct token_list *tokens, size_t *index)
{
    *index += 1;

    // check for compound list
    compound_list_check(tokens, index);

    if (*index >= tokens->size)
        errx(2, "grammar error: exepected something after 'else'");

    // in any cases, there is a 'fi' after a 'else'
    else if (tokens->list[*index]->type != TOKEN_FI)
        errx(2, "grammar error in if: expected 'fi'");

    else
    {
        *index += 1;
        return 1;
    }
}

static int if_check(struct token_list *tokens, size_t *index)
{
    *index += 1;

    // check for compound_list
    compound_list_check(tokens, index);

    // we generally are on the 'then'

    if (*index >= tokens->size || tokens->list[*index]->type != TOKEN_THEN)
        errx(2, "grammar error in if: expected 'then'");

    *index += 1;

    // check for compound list
    compound_list_check(tokens, index);

    // we generally are on 'fi' or other command
    if (*index >= tokens->size)
        errx(2, "grammar error: expected 'fi'");

    else if (tokens->list[*index]->type == TOKEN_FI)
    {
        *index += 2;
        return 1;
    }
    else if (tokens->list[*index]->type == TOKEN_ELIF)
        if_check(tokens, index);

    else if (tokens->list[*index]->type == TOKEN_ELSE)
        else_check(tokens, index);

    else
        errx(2, "grammar error in if: expected something at the end");

    return 1;
}

static int for_check(struct token_list *tokens, size_t *index)
{
    *index += 1;
    if (*index >= tokens->size)
        errx(2, "grammar error: expected something after 'for'");

    if (tokens->list[*index]->type != TOKEN_WORDS)
        errx(2, "grammar error in for's variable: expected 'words'");

    *index += 1;
    if (*index >= tokens->size || tokens->list[*index]->type != TOKEN_IN)
        errx(2, "Grammar error in for's variable: expected 'in'");

    *index += 1;
    if (*index >= tokens->size)
        errx(2, "grammar error: expected something after 'in'");

    words_list_check(tokens, index);

    if (tokens->list[*index]->type != TOKEN_DO)
        errx(2, "grammar error: expected 'do' after ';'");

    *index += 1;
    if (*index >= tokens->size)
        errx(2, "grammar error: expected something after 'do'");

    compound_list_check(tokens, index);

    if (*index >= tokens->size || tokens->list[*index]->type != TOKEN_DONE)
        errx(2, "grammar error: expected 'done' after ';'");

    *index += 2;
    return 1;
}

static int while_check(struct token_list *tokens, size_t *index)
{
    *index += 1;

    if (*index >= tokens->size)
        errx(2, "grammar error: expected something after 'while'");

    compound_list_check(tokens, index);

    if (*index >= tokens->size || tokens->list[*index]->type != TOKEN_DO)
        errx(2, "grammar error: expected 'do' after compound list in while");

    *index += 1;
    if (*index >= tokens->size)
        errx(2, "grammar error: expected something after 'do'");

    compound_list_check(tokens, index);

    if (*index >= tokens->size || tokens->list[*index]->type != TOKEN_DONE)
        errx(2, "grammar error: expected 'done' after compound list in while");

    *index += 2;
    return 1;
}

static int until_check(struct token_list *tokens, size_t *index)
{
    *index += 1;

    if (*index >= tokens->size)
        errx(2, "grammar error: expected something after 'until'");

    compound_list_check(tokens, index);

    if (*index >= tokens->size || tokens->list[*index]->type != TOKEN_DO)
        errx(2, "grammar error: expected 'do' after compound list in until");

    *index += 1;
    if (*index >= tokens->size)
        errx(2, "grammar error: expected something after 'do'");

    compound_list_check(tokens, index);

    if (*index >= tokens->size || tokens->list[*index]->type != TOKEN_DONE)
        errx(2, "grammar error: expected 'done' after compound list in until");

    *index += 2;
    return 1;
}

static int compound_list_check(struct token_list *tokens, size_t *index)
{
    if (tokens->list[*index]->type == TOKEN_NEG)
        *index += 1;

    while (*index < tokens->size
           && (tokens->list[*index]->type == TOKEN_WORDS
               || tokens->list[*index]->type == TOKEN_IF
               || tokens->list[*index]->type == TOKEN_FOR
               || tokens->list[*index]->type == TOKEN_WHILE
               || tokens->list[*index]->type == TOKEN_UNTIL))
    {
        if (tokens->list[*index]->type == TOKEN_WORDS)
            words_list_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_IF)
            if_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_FOR)
            for_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_WHILE)
            while_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_UNTIL)
            until_check(tokens, index);
    }

    return 1;
}

int grammar_check(struct token_list *tokens)
{
    size_t *index = malloc(sizeof(size_t));
    *index = 0;

    while (*index < tokens->size)
    {
        if ((tokens->list[*index]->type == TOKEN_WORDS
             && (strcmp(tokens->list[*index]->data, "&") || *index != 0))
            || tokens->list[*index]->type == TOKEN_NEG
            || tokens->list[*index]->type == TOKEN_REDIR)
            words_list_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_IF)
            if_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_COLON && *index != 0)
            *index += 1;

        else if (tokens->list[*index]->type == TOKEN_FOR)
            for_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_WHILE)
            while_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_UNTIL)
            until_check(tokens, index);

        else if (tokens->list[*index]->type == TOKEN_BRACKET_OPEN)
        {
            *index += 1;
            compound_list_check(tokens, index);

            if (*index >= tokens->size)
                errx(2, "grammar error: expected '}'");

            if (tokens->list[*index]->type != TOKEN_BRACKET_CLOSE)
                errx(2, "grammar error: missing '}'");

            *index += 1;

            if (*index < tokens->size
                && (tokens->list[*index]->type == TOKEN_COLON
                    || tokens->list[*index]->type == TOKEN_AND
                    || tokens->list[*index]->type == TOKEN_OR
                    || tokens->list[*index]->type == TOKEN_PIPE))
                *index += 1;

            if (*index >= tokens->size)
            {
                errx(2, "grammar error after 'operator'");
            }
        }
        else
            errx(2, "grammar error after ';'");
    }

    free(index);
    return 1;
}
