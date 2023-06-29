#include <stdio.h>
#include <stdlib.h>

#include "./project/builtins.h"
#include "./project/executer.h"
#include "./project/expressions.h"
#include "./project/free.h"
#include "./project/lexer.h"
#include "./project/parser.h"
#include "./project/pretty_print.h"
#include "project/variable.h"

int main(int argc, char **argv)
{
    struct token_list *tokens = tokens_init(argc, argv);

    struct ast_node *tree = parser(tokens);

    struct var_list *var_list = init_var_list(argc, argv);

    int res = execute(tree, var_list);

    token_list_free(tokens);
    tree_free(tree);
    var_list_free(var_list);

    return res;
}
