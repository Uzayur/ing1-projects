#ifndef FREE_H
#define FREE_H

#include "expressions.h"

void token_list_free(struct token_list *list);
void tree_free(struct ast_node *tree);
void var_list_free(struct var_list *list);

#endif /* ! FREE_H */
