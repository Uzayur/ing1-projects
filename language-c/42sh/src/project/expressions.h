#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <err.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

enum token_type
{
    TOKEN_IF = 0,
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_FI,
    TOKEN_FOR,
    TOKEN_IN,
    TOKEN_WHILE,
    TOKEN_UNTIL,
    TOKEN_DO,
    TOKEN_DONE,
    TOKEN_COLON,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_PIPE,
    TOKEN_NEG,
    TOKEN_REDIR,
    TOKEN_BRACKET_OPEN,
    TOKEN_BRACKET_CLOSE,
    TOKEN_WORDS
};

struct token
{
    enum token_type type;
    char *data;
};

struct token_list
{
    struct token **list;
    size_t size;
    size_t capacity;
};

enum node_type // je ne suis pas vraiment sur de l'utilite de cet enum puisque
               // maintenant on a un ast_command et condition => facilement
               // modifiable dans tous les cas
{
    TYPE_IF = 0,
    TYPE_ELIF,
    TYPE_COMMAND,
    TYPE_WHILE,
    TYPE_UNTIL,
    TYPE_AND,
    TYPE_OR,
    TYPE_PIPE,
    TYPE_NEG,
    TYPE_COLON,
    TYPE_FOR,
    TYPE_BRACKET
};

struct ast_command
{
    size_t size;
    char **argv;
};

struct ast_while
{
    struct ast_node *wcond;
    struct ast_node *wdo;
};

struct ast_until
{
    struct ast_node *ucond;
    struct ast_node *udo;
};

struct ast_if
{
    struct ast_node
        *cond; // autre struct pour faciliter la gestion de la memoire
    struct ast_node *then; // vers une commande ou un autre if (peut etre NULL)
    struct ast_node *elif; // vers else ou elif (peut etre NULL)
};

struct ast_and
{
    struct ast_node *node1;
    struct ast_node *node2;
};

struct ast_or
{
    struct ast_node *node1;
    struct ast_node *node2;
};

struct ast_pipe
{
    struct ast_node *node1;
    struct ast_node *node2;
};

struct ast_neg
{
    struct ast_node *node1;
};

struct ast_elif
{
    struct ast_node *cond;
    struct ast_node *then;
    struct ast_node *elif;
};

struct ast_for
{
    char *name;
    char **word;
    size_t size;
    struct ast_node *fdo;
};

struct ast_cb
{
    struct token_list *tok;
};

union ast_data
{
    struct ast_command *ast_command;
    struct ast_if *ast_if;
    struct ast_elif *ast_elif;
    struct ast_while *ast_while;
    struct ast_until *ast_until;
    struct ast_and *ast_and;
    struct ast_or *ast_or;
    struct ast_pipe *ast_pipe;
    struct ast_neg *ast_neg;
    struct ast_for *ast_for;
    struct ast_cb *ast_cb;
    // pointeurs donc ->
    // rajouter les struct operateurs dans le futur
};

struct ast_node
{
    enum node_type type; // type: if, command, operateurs...
    union ast_data *data; // la data depend du type
    struct ast_node *next;
};

struct var
{
    char *name;
    size_t size;
    char **value;
};

struct var_list
{
    struct var **list;
    size_t size;
    size_t capacity;
};

#endif /* ! EXPRESSIONS_H */
