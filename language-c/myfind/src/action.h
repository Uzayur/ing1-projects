#ifndef ACTION_H
#define ACTION_H

#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "expression.h"

int evaluate(struct node *ast, int argc, char *argv[], int token);

#endif /* ! ACTION_H */
