#include "lexer.h"

#include "grammar.h"
#include "pretty_print.h"

static size_t identify_redirection(char *buf)
{
    if (!strcmp(buf, ">") || !strcmp(buf, "<") || !strcmp(buf, ">&")
        || !strcmp(buf, "<&") || !strcmp(buf, ">>") || !strcmp(buf, "<>")
        || !strcmp(buf, ">|"))
        return 0;
    return 1;
}

static size_t redirection_size(char *buf, size_t index)
{
    if (buf[index + 1] == '&' || buf[index + 1] == '|' || buf[index + 1] == '>')
        return 2;
    return 1;
}

static size_t my_strlen(char *buf, size_t index)
{
    if (buf[index] == ';')
        return 1;
    else if (buf[index] == '>' || buf[index] == '<')
        return redirection_size(buf, index);
    else if (buf[index] == '{' && buf[index + 1] == ' ')
        return 1;

    // if we haven't quote
    size_t size = 0;
    while (buf[index] != ' ' && buf[index] != '\0' && buf[index] != ';'
           && buf[index] != '>' && buf[index] != '<' && buf[index] != '\n')
    {
        if (buf[index] == 39)
        {
            size++;
            index++;
            while (buf[index] != 39)
            {
                if (buf[index] == '\0')
                    errx(2, "error: missing '");
                size++;
                index++;
            }
            size++;
            index++;
        }
        else if (buf[index] == '"')
        {
            size++;
            index++;
            while (buf[index] != '"')
            {
                if (buf[index] == '\0')
                    errx(2, "error: missing \"");
                size++;
                index++;
            }
            size++;
            index++;
        }
        else
        {
            index++;
            size++;
        }
    }
    return size;
}

static void add_token_colon(struct token_list *tokens)
{
    struct token *tok = malloc(sizeof(struct token));
    tok->type = TOKEN_COLON;
    tok->data = calloc(2, sizeof(char));
    tok->data[0] = ';';

    if (tokens->size == tokens->capacity)
    {
        tokens->capacity = tokens->capacity * 2;
        tokens->list =
            realloc(tokens->list, sizeof(struct token *) * tokens->capacity);
    }

    tokens->list[tokens->size++] = tok;
}

static void identify_token(struct token *tok, int previous)
{
    if (!strcmp(tok->data, "if") && previous != 2)
        tok->type = TOKEN_IF;
    else if (!strcmp(tok->data, "then") && previous != 2)
        tok->type = TOKEN_THEN;
    else if (!strcmp(tok->data, "elif") && previous != 2)
        tok->type = TOKEN_ELIF;
    else if (!strcmp(tok->data, "else") && previous != 2)
        tok->type = TOKEN_ELSE;
    else if (!strcmp(tok->data, "fi") && previous != 2)
        tok->type = TOKEN_FI;
    else if (!strcmp(tok->data, "for") && previous != 2)
        tok->type = TOKEN_FOR;
    else if (!strcmp(tok->data, "in") && previous < 0)
        tok->type = TOKEN_IN;
    else if (!strcmp(tok->data, "in") && previous != 2)
        tok->type = TOKEN_IN;
    else if (!strcmp(tok->data, "while") && previous != 2)
        tok->type = TOKEN_WHILE;
    else if (!strcmp(tok->data, "until") && previous != 2)
        tok->type = TOKEN_UNTIL;
    else if (!strcmp(tok->data, "do") && previous != 2)
        tok->type = TOKEN_DO;
    else if (!strcmp(tok->data, "done") && previous != 2)
        tok->type = TOKEN_DONE;
    else if (!strcmp(tok->data, ";"))
        tok->type = TOKEN_COLON;
    else if (!strcmp(tok->data, "&&"))
        tok->type = TOKEN_AND;
    else if (!strcmp(tok->data, "||"))
        tok->type = TOKEN_OR;
    else if (!strcmp(tok->data, "|"))
        tok->type = TOKEN_PIPE;
    else if (!strcmp(tok->data, "!") && previous != 2)
        tok->type = TOKEN_NEG;
    else if (!identify_redirection(tok->data))
        tok->type = TOKEN_REDIR;
    else if (!strcmp(tok->data, "{") && previous == 2)
        tok->type = TOKEN_WORDS;
    else if (!strcmp(tok->data, "{"))
        tok->type = TOKEN_BRACKET_OPEN;
    else if (!strcmp(tok->data, "}") && previous == 2)
        tok->type = TOKEN_WORDS;
    else if (!strcmp(tok->data, "}") && !previous)
        tok->type = TOKEN_BRACKET_CLOSE;
    else
        tok->type = TOKEN_WORDS;
}

static int identify_previous_token(struct token_list *tokens)
{
    int type = tokens->list[tokens->size - 1]->type;
    if (type == TOKEN_IF || type == TOKEN_THEN || type == TOKEN_ELIF
        || type == TOKEN_ELSE || type == TOKEN_FOR || type == TOKEN_IN
        || type == TOKEN_WHILE || type == TOKEN_UNTIL || type == TOKEN_DO
        || type == TOKEN_COLON || type == TOKEN_AND || type == TOKEN_OR
        || type == TOKEN_PIPE || type == TOKEN_NEG || type == TOKEN_REDIR
        || type == TOKEN_BRACKET_OPEN)
        return 0;
    return 1;
}

static void lex(char *buffer, struct token_list *tokens)
{
    size_t buf_index = 0;

    int previous = 0;
    while (buffer[buf_index] != '\0')
    {
        struct token *tok = malloc(sizeof(struct token));

        int size = my_strlen(buffer, buf_index);

        tok->data = calloc(2048, sizeof(char));
        size_t tok_ind = 0;

        // copy the part of the buffer needed
        for (int i = 0; i < size; i++)
            tok->data[tok_ind++] = buffer[buf_index++];
        tok->data[tok_ind] = '\0';

        // check the size of tokens
        if (tokens->size == tokens->capacity)
        {
            tokens->capacity = tokens->capacity * 2;
            tokens->list = realloc(tokens->list,
                                   sizeof(struct token *) * tokens->capacity);
        }

        tokens->list[tokens->size] = tok;
        identify_token(tokens->list[tokens->size], previous);

        // in case of 'in' in for command
        if (tokens->size != 0
            && tokens->list[tokens->size - 1]->type == TOKEN_FOR)
            previous = -1;
        else if (tokens->list[tokens->size]->type == TOKEN_COLON)
            previous = 0;
        else if (tokens->list[tokens->size]->type == TOKEN_WORDS)
            previous = 2;
        else
            previous = 1;

        tokens->size++;

        if (buffer[buf_index] == '\n' && identify_previous_token(tokens))
        {
            add_token_colon(tokens);
            previous = 0;
            buf_index++;

            while (buffer[buf_index] == '\n' || buffer[buf_index] == ' ')
                buf_index++;
        }
        else
        {
            while (buffer[buf_index] == ' ' || buffer[buf_index] == '\n')
                buf_index++;
        }
    }
}

static struct token_list *create_token_list(void)
{
    struct token_list *tokens = malloc(sizeof(struct token_list));

    tokens->capacity = 16;
    tokens->list = malloc(sizeof(struct token *) * tokens->capacity);
    tokens->size = 0;

    return tokens;
}

static struct token_list *tokens_from_input(struct token_list *tokens)
{
    char character;
    char *buffer = malloc(sizeof(char) * 8192);
    size_t size = 0;

    while (read(0, &character, 1)) // heap buffer
        buffer[size++] = character;
    buffer[size] = '\0';

    lex(buffer, tokens);
    free(buffer);
    return tokens;
}

static struct token_list *tokens_from_file(struct token_list *tokens,
                                           char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
        return NULL;

    char *buffer = malloc(sizeof(char) * 8192);
    size_t size = 0;
    char character;
    while ((character = fgetc(file)) != EOF)
        buffer[size++] = character;
    buffer[size] = '\0';

    lex(buffer, tokens);
    free(buffer);
    return tokens;
}

struct token_list *tokens_init(int argc, char *argv[])
{
    struct token_list *tokens = create_token_list();

    if (argc == 1)
        tokens_from_input(tokens);

    else if (strcmp(argv[1], "-c"))
        tokens_from_file(tokens, argv[1]);

    else if (!strcmp(argv[1], "-c") && argc == 3)
        lex(argv[argc - 1], tokens);

    grammar_check(tokens);

    return tokens;
}
