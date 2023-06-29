#ifndef BUILTINS_H
#define BUILTINS_H

#include "expressions.h"

int execute_echo(struct ast_command *cmd);
int execute_exit(struct ast_command *cmd);
int execute_cd(struct ast_command *cmd, struct var_list *var);
int execute_export(struct ast_command *cmd);
int execute_dot(struct ast_command *cmd);
int execute_break(struct ast_command *cmd);

#endif /* ! BUILTINS_H */
