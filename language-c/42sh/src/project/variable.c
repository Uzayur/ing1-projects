#define _POSIX_C_SOURCE 200809L

#include "variable.h"

#include "expressions.h"

static int new_size(char c, const char *str, const char *pattern)
{
    int pattern_size = 0;

    if (pattern != NULL)
    {
        while (pattern[pattern_size] != '\0')
            pattern_size++;
    }

    int size = 0;
    int index = 0;

    while (str[index] != '\0')
    {
        if (str[index] == c)
            size += pattern_size;
        else
            size++;
        index++;
    }

    return size + 1;
}

char *string_replace(char c, const char *str, const char *pattern)
{
    if (!str)
        return NULL;

    char *dest = malloc(sizeof(char) * new_size(c, str, pattern));

    int str_index = 0;
    int dest_index = 0;
    while (str[str_index] != '\0')
    {
        if (str[str_index] == c)
        {
            int pattern_index = 0;
            while (pattern && pattern[pattern_index] != '\0')
            {
                dest[dest_index] = pattern[pattern_index];
                pattern_index++;
                dest_index++;
            }
        }
        else
        {
            dest[dest_index] = str[str_index];
            dest_index++;
        }
        str_index++;
    }
    dest[new_size(c, str, pattern) - 1] = '\0';
    return dest;
}

static char *concat(char *args, int argc, char *argv[])
{
    size_t taille = 0;
    for (int index = 2; index < argc; index++)
    {
        taille += strlen(argv[index]) + 1;
    }
    size_t index = 0;
    for (int i = 2; i < argc; i++)
    {
        size_t j = 0;
        while (argv[i][j] != '\0')
        {
            args[index] = argv[i][j];
            index++;
            j++;
        }
        args[index] = ' ';
        index++;
    }
    args[index - 1] = '\0';
    return args;
}

char *my_itoa(int value, char *s)
{
    int index = 0;

    if (value < 0)
    {
        s[index] = '=';
        value = -value;
        index++;
    }

    int index_pui = 10;

    while (value / index_pui > 9)
        index_pui *= 10;

    while (value > 9)
    {
        s[index] = '0' + value / index_pui;
        value = value % index_pui;
        index_pui /= 10;
        index++;
    }
    s[index] = '0' + value;
    s[index + 1] = '\0';
    return s;
}

static struct var *init_var(void)
{
    struct var *new = malloc(sizeof(struct var));

    new->name = NULL;
    new->value = NULL;
    new->size = 0;

    return new;
}

static struct var_list *push_var(struct var_list *list, char *name,
                                 char **value, size_t size)
{
    if (list->size == list->capacity)
    {
        list->capacity = list->capacity * 2;
        list->list = realloc(list, list->capacity);
    }

    struct var *new = init_var();

    new->name = name;
    new->value = value;
    new->size = size;

    list->list[list->size] = new;

    list->size++;

    return list;
}

static void init_at(struct var_list *var, int argc, char *argv[])
{
    char *name = malloc(3 * sizeof(char));
    name[0] = '"';
    name[1] = '@';
    name[2] = '\0';

    size_t count = 0;
    char **value = malloc((argc - 1) * sizeof(char *));
    for (int i = 2; i < argc; i++)
    {
        value[i - 2] = malloc((strlen(argv[i]) + 1) * sizeof(char));
        value[i - 2] = strcpy(value[i - 2], argv[i]);
        count++;
    }
    push_var(var, name, value, count);

    char *name_bis = malloc(2 * sizeof(char));
    name_bis[0] = '@';
    name_bis[1] = '\0';

    count = 0;
    char **value_bis = NULL;

    char *arg = malloc(500 * sizeof(char));
    concat(arg, argc, argv);
    char *tok = NULL;
    char *args = arg;
    while ((tok = strtok_r(args, " ", &args)))
    {
        value_bis = realloc(value_bis, ++count * sizeof(char *));
        int idx = 0;
        value_bis[count - 1] = malloc((strlen(tok) + 1) * sizeof(char));
        while (tok[idx] != '\0')
        {
            value_bis[count - 1][idx] = tok[idx];
            idx++;
        }
        value_bis[count - 1][idx] = '\0';
    }
    free(arg);

    push_var(var, name_bis, value_bis, count);
}

static void init_star(struct var_list *var, int argc, char *argv[])
{
    char *name_s = malloc(3 * sizeof(char));
    name_s[0] = '"';
    name_s[1] = '*';
    name_s[2] = '\0';

    char **value_bis = malloc(1 * sizeof(char *));
    value_bis[0] = malloc(500 * sizeof(char));
    concat(value_bis[0], argc, argv);

    push_var(var, name_s, value_bis, 1);

    char *name = malloc(2 * sizeof(char));
    name[0] = '*';
    name[1] = '\0';

    size_t count = 0;
    char **value = NULL;

    char *arg = malloc(500 * sizeof(char));
    concat(arg, argc, argv);
    char *tok = NULL;
    char *args = arg;
    while ((tok = strtok_r(args, " ", &args)))
    {
        value = realloc(value, ++count * sizeof(char *));
        int idx = 0;
        value[count - 1] = malloc((strlen(tok) + 1) * sizeof(char));
        while (tok[idx] != '\0')
        {
            value[count - 1][idx] = tok[idx];
            idx++;
        }
        value[count - 1][idx] = '\0';
    }
    free(arg);

    push_var(var, name, value, count);
}

static char *copy_string(char *s)
{
    char *new = malloc(sizeof(char) * (strlen(s) + 1));
    int index = 0;

    while (s[index] != 0)
    {
        new[index] = s[index];
        index++;
    }
    new[index] = '\0';

    return new;
}

static void init_basics_var(struct var_list *var)
{
    char *name = calloc(2, sizeof(char));
    name[0] = '$';

    char **value = malloc(sizeof(char *));
    value[0] = malloc(sizeof(char) * 10);
    my_itoa(getpid(), value[0]);

    push_var(var, name, value, 1);

    char *name2 = copy_string("RANDOM");
    char **value2 = malloc(sizeof(char *));
    value2[0] = malloc(sizeof(char) * 10);
    srand(time(NULL));
    my_itoa(rand() % 32768, value2[0]);

    push_var(var, name2, value2, 1);

    char *name3 = copy_string("UID");
    char **value3 = malloc(sizeof(char *));
    value3[0] = malloc(sizeof(char) * 10);
    my_itoa(getuid(), value3[0]);

    push_var(var, name3, value3, 1);

    char *name4 = copy_string("OLDPWD");
    char **value4 = malloc(sizeof(char *) * 2);
    value4[0] = calloc(1024, sizeof(char));
    value4[0] = getcwd(value4[0], 1024);

    push_var(var, name4, value4, 1);

    char *name5 = copy_string("PWD");
    char **value5 = malloc(sizeof(char *) * 2);
    value5[0] = calloc(1024, sizeof(char));
    value5[0] = getcwd(value5[0], 1024);

    push_var(var, name5, value5, 1);

    char *name6 = copy_string("IFS");
    char **value6 = malloc(sizeof(char *));
    value6[0] = calloc(128, sizeof(char));

    push_var(var, name6, value6, 1);
}

struct var_list *init_var_list(int argc, char *argv[])
{
    struct var_list *var = malloc(sizeof(struct var_list));

    var->capacity = 32;
    var->size = 0;
    var->list = malloc(sizeof(struct var) * var->capacity);

    // Init $1 $2 ..... $n
    if ((argc > 2) && strcmp(argv[1], "-c"))
    {
        for (int indice = 1; indice < argc; indice++)
        {
            char *name = malloc(3 * sizeof(char));
            name = my_itoa(indice - 1, name);
            char **value = malloc(1 * sizeof(char *));
            char *deep_value =
                malloc((strlen(argv[indice]) + 1) * sizeof(char));
            deep_value = strcpy(deep_value, argv[indice]);
            value[0] = deep_value;
            push_var(var, name, value, 1);
        }

        init_at(var, argc, argv);
        init_star(var, argc, argv);
    }
    char *name = malloc(2 * sizeof(char));
    name[0] = '#';
    name[1] = '\0';

    char **value = malloc(sizeof(char *));
    value[0] = calloc(10, sizeof(char));

    if ((argc > 1) && strcmp(argv[1], "-c"))
        my_itoa(argc - 2, value[0]);
    else
        value[0][0] = '0';

    push_var(var, name, value, 1);

    char *name_bis = malloc(2 * sizeof(char));
    name_bis[0] = '?';
    name_bis[1] = '\0';

    char **value_bis = malloc(sizeof(char *));
    value_bis[0] = malloc(sizeof(char) * 10);
    value_bis[0][0] = '0';
    value_bis[0][1] = '\0';

    push_var(var, name_bis, value_bis, 1);

    init_basics_var(var);

    return var;
}

int is_var(struct var_list *var, char *name)
{
    for (size_t indice = 0; indice < var->size; indice++)
    {
        if (!strcmp(name, var->list[indice]->name))
            return indice;
    }
    return -1;
}

int search_var(char *arg, struct var_list *list)
{
    int indice = 0;
    char *name = calloc(strlen(arg) + 1, sizeof(char));
    char **value = malloc(sizeof(char *));
    value[0] = calloc(strlen(arg) + 512, sizeof(char));
    int name_idx = 0;
    int value_idx = 0;

    if (arg[indice] != '_' && !('A' <= arg[indice] && arg[indice] <= 'Z')
        && !('a' <= arg[indice] && arg[indice] <= 'z'))
    {
        free(name);
        free(value[0]);
        free(value);
        return 0;
    }

    while (arg[indice] != '\0' && arg[indice] != '=' && arg[indice] != ' ')
        name[name_idx++] = arg[indice++];

    if (arg[indice++] != '=')
    {
        free(name);
        free(value[0]);
        free(value);
        return 0;
    }

    if (arg[indice] == '"')
    {
        indice++;
        int previous = 1;
        while (arg[indice] != '\0' && arg[indice] != '"')
        {
            if (arg[indice] == ' ' && previous)
                indice++;
            else
                value[0][value_idx++] = arg[indice++];

            if (arg[indice - 1] == ' ')
                previous = 1;
            else
                previous = 0;
        }
        if (value[0][value_idx - 1] == ' ')
            value[0][value_idx - 1] = '\0';

        char *dest = string_replace('"', value[0], "");
        free(value[0]);
        value[0] = dest;
    }
    else if (arg[indice] == 39)
    {
        indice++;
        int previous = 1;
        while (arg[indice] != '\0'
               && (arg[indice] != 39 || isalnum(arg[indice + 1])))
        {
            if (arg[indice] == ' ' && previous)
                indice++;
            else
                value[0][value_idx++] = arg[indice++];

            if (arg[indice - 1] == ' ')
                previous = 1;
            else
                previous = 0;
        }

        if (value[0][value_idx - 1] == ' ')
            value[0][value_idx - 1] = '\0';

        char *dest = string_replace(39, value[0], "");
        free(value[0]);
        value[0] = dest;
    }
    else
    {
        while (arg[indice] != '\0')
        {
            if (arg[indice] == ' ')
                errx(127, "error in var affectation");
            value[0][value_idx++] = arg[indice++];
        }
    }

    int new_ind = is_var(list, name);
    if (new_ind == -1)
        list = push_var(list, name, value, 1);

    else
    {
        size_t index = 0;
        while (value[0][index] != '\0')
        {
            list->list[new_ind]->value[0][index] = value[0][index];
            index++;
        }
        free(value[0]);
        free(value);
        free(name);
    }

    return 1;
}
