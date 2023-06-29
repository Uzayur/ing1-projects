#define _XOPEN_SOURCE 700

#include "action.h"

#include "expression.h"

static int name_action(char *starting, char *name)
{
    DIR *dir = opendir(starting);
    if (!dir)
        return 0;

    struct dirent *directory;

    if (!(directory = readdir(dir)) && fnmatch(name, directory->d_name, 0) == 0)
        printf("%s/%s\n", starting, directory->d_name);

    while (directory)
    {
        if (!fnmatch(name, directory->d_name, 0))
            printf("%s/%s\n", starting, directory->d_name);

        if (strcmp(directory->d_name, ".") && strcmp(directory->d_name, ".."))
        {
            char *path =
                malloc(sizeof(char)
                       * (strlen(starting) + strlen(directory->d_name) + 2));

            for (size_t i = 0; i < strlen(starting); ++i)
                path[i] = starting[i];

            path[strlen(starting)] = '/';

            for (size_t j = 0; j < strlen(directory->d_name); ++j)
                path[strlen(starting) + 1 + j] = directory->d_name[j];

            path[strlen(starting) + strlen(directory->d_name) + 1] = '\0';

            name_action(path, name);
            free(path);
        }
        directory = readdir(dir);
    }
    closedir(dir);
    return 0;
}

static int execute_name(int argc, char *argv[], char *name, int token)
{
    int count = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
            break;
        DIR *dir = opendir(argv[i]);
        if (!dir)
        {
            fprintf(stderr, "myfind: ‘%s‘: No such file or directory\n",
                    argv[i]);
            count++;
        }
        closedir(dir);
    }

    if (token < 2)
        return 0;

    else if (token != 2)
        return (count > 0);

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (i == 1)
                count += name_action(".", name);
            return (count > 0);
        }

        DIR *dir = opendir(argv[i]);

        if (dir && !fnmatch(name, argv[i], 0))
            printf("%s\n", argv[i]);

        count += name_action(argv[i], name);
        closedir(dir);
    }
    return 1;
}

static int test_type(struct stat buf, char *type)
{
    if (!strcmp(type, "b"))
        return S_ISBLK(buf.st_mode);

    else if (!strcmp(type, "c"))
        return S_ISCHR(buf.st_mode);

    else if (!strcmp(type, "d"))
        return S_ISDIR(buf.st_mode);

    else if (!strcmp(type, "f"))
        return S_ISREG(buf.st_mode);

    else if (!strcmp(type, "l"))
        return S_ISLNK(buf.st_mode);

    else if (!strcmp(type, "p"))
        return S_ISFIFO(buf.st_mode);

    else if (!strcmp(type, "s"))
        return S_ISSOCK(buf.st_mode);

    else
    {
        fprintf(stderr, "myfind:  Unknown argument to -type: %s\n", type);
        exit(1);
    }
}

static char *init_path(char *path, char *new_name)
{
    int size = strlen(path) + strlen(new_name) + 2;
    char *new_path = malloc(sizeof(char) * size);

    for (size_t i = 0; i < strlen(path); ++i)
        new_path[i] = path[i];

    new_path[strlen(path)] = '/';

    for (size_t j = 0; j < strlen(new_name); ++j)
        new_path[strlen(path) + 1 + j] = new_name[j];

    new_path[size - 1] = '\0';
    return new_path;
}

static int type_action(char *path, char *type)
{
    DIR *dir = opendir(path);
    if (!dir)
        return 0;

    struct stat buff;
    struct dirent *directory;

    if (!(directory = readdir(dir)))
    {
        stat(init_path(path, directory->d_name), &buff);
        if (test_type(buff, type))
            printf("%s/%s\n", path, directory->d_name);
    }

    while (directory)
    {
        if (strcmp(directory->d_name, ".") && strcmp(directory->d_name, ".."))
        {
            char *new_path = init_path(path, directory->d_name);
            stat(new_path, &buff);
            if (test_type(buff, type))
                printf("%s\n", new_path);

            type_action(new_path, type);
            free(new_path);
        }
        directory = readdir(dir);
    }
    closedir(dir);
    return 0;
}

static int execute_type(int argc, char *argv[], char *type, int token)
{
    if (token < 2)
        return 0;
    else if (token != 2)
        return 1;

    int count = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (i == 1)
                type_action(".", argv[i]);
            return (count > 0);
        }

        struct stat buff;
        if (stat(argv[i], &buff))
        {
            count++;
            fprintf(stderr, "myfind: %s:No such file or directory\n", argv[i]);
        }
        else if (!stat(argv[i], &buff) && test_type(buff, type))
        {
            printf("%s\n", argv[i]);
            DIR *dir = opendir(argv[i]);
            if (dir)
                type_action(argv[i], type);
            closedir(dir);
        }
    }
    return 1;
}

int evaluate(struct node *ast, int argc, char *argv[], int token)
{
    struct function name = { NAME, execute_name };
    struct function type = { TYPE, execute_type };
    struct function funs[2] = { name, type };
    int funs_len = 2;

    if (ast->type == OR)
    {
        return evaluate(ast->left, argc, argv, ast->right->type)
            || evaluate(ast->right, argc, argv, 2);
    }
    else if (ast->type == AND)
    {
        return evaluate(ast->left, argc, argv, ast->right->type)
            && evaluate(ast->right, argc, argv, 2);
    }
    else
    {
        for (int i = 0; i < funs_len; i++)
        {
            if (funs[i].type == ast->type)
                return funs[i].fun(argc, argv, ast->value, token);
        }
        return 1;
    }
}
