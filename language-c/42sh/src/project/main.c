#include "executer.h"
#include "expressions.h"
#include "free.h"
#include "lexer.h"
#include "parser.h"
#include "pretty_print.h"
#include "variable.h"

int main(int argc, char **argv)
{
    struct token_list *tokens = tokens_init(argc, argv);

    struct ast_node *tree = parser(tokens);

    // INIT VAR LIST
    struct var_list *var = init_var_list(argc, argv);

    // PRINT CASE
    pretty_print(tree, tokens, var);

    // EXECUTE CASES
    int return_value = execute(tree, var);

    // PRINT VAR AFTER EXECUTION
    pretty_print_var(var);

    printf("\n###### END ######\n");

    // FREE
    token_list_free(tokens);
    tree_free(tree);
    var_list_free(var);

    return return_value;
}
