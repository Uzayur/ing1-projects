#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H

#include "expressions.h"

void pretty_print(struct ast_node *tree, struct token_list *tokens,
                  struct var_list *var);
void pretty_print_var(struct var_list *var);

#endif /* ! PRETTY_PRINT_H */
