#ifndef HANDLE_STACK_H
#define HANDLE_STACK_H

struct variables *stack_push_var(struct variables *s, char *names, char *val);
struct rules *stack_push_rule(struct rules *s, char *name, char **dep_list);

#endif
