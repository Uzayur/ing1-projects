#ifndef VARIABLE_H
#define VARIABLE_H

struct var_list *init_var_list(int argc, char *argv[]);
int search_var(char *arg, struct var_list *list);
int is_var(struct var_list *var, char *name);
char *my_itoa(int value, char *s);
char *string_replace(char c, const char *str, const char *pattern);

#endif /* !VARIABLE_H */
