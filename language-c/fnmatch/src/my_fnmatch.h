#ifndef MY_FNMATCH_H
#define MY_FNMATCH_H

int my_fnmatch(const char *pattern, const char *string);

int hook_calcul(const char *pattern, const char *string, int pattern_ind,
int string_ind);

#endif /* !MY_FNMATCH_H */
