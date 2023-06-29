#ifndef EXECUTER_H
#define EXECUTER_H

#include "expressions.h"

int execute(struct ast_node *node, struct var_list *var_list);

#endif /* EXECUTER_H */
