#ifndef PARSER_H
#define PARSER_H

#include "expressions.h"

struct ast_node *parser(struct token_list *tokens);
struct ast_node *create_node(struct token_list *tokens, size_t *index,
                             int mode);
#endif /* ! PARSER_H */
