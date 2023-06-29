#include "myfind.h"

static char *edit_path(char *path)
{
    if (path[strlen(path) - 1] == '/')
        path[strlen(path) - 1] = '\0';

    return path;
}

int print_arg(char *path)
{
    path = edit_path(path);
    DIR *dir = opendir(path);

    if (dir == NULL)
        return 1;

    struct dirent *directory;

    if ((directory = readdir(dir)) == NULL)
        printf("%s/%s\n", path, directory->d_name);

    while (directory != NULL)
    {
        char *name = directory->d_name;
        if (strcmp(name, ".") && strcmp(name, ".."))
        {
            printf("%s/%s\n", path, directory->d_name);

            char *new_path =
                malloc(sizeof(char) * (strlen(path) + strlen(name) + 2));

            for (size_t i = 0; i < strlen(path); i++)
                new_path[i] = path[i];

            new_path[strlen(path)] = '/';

            for (size_t j = 0; j < strlen(name); j++)
                new_path[strlen(path) + 1 + j] = name[j];

            new_path[strlen(path) + 1 + strlen(name)] = '\0';

            print_arg(new_path);
            free(new_path);
        }
        directory = readdir(dir);
    }
    closedir(dir);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf(".\n");
        return print_arg(".");
    }

    int command_count = 0;
    for (int i = 0; i < argc; ++i)
    {
        if (argv[i][0] == '-')
            command_count++;
    }

    if (command_count == 0)
    {
        int test = 0;
        for (int i = 1; i < argc; ++i)
        {
            DIR *dir = opendir(argv[i]);
            if (dir == NULL)
            {
                fprintf(stderr, "myfind: ‘%s‘ : No file or dir\n", argv[i]);
                test++;
            }
            else
            {
                printf("%s\n", argv[i]);
                print_arg(argv[i]);
            }
            closedir(dir);
        }
        return 0 + (test > 0);
    }
    else
    {
        int index = 0;
        while (argv[index][0] != '-')
            index++;
        return parser(argc, argv, index);
    }
    return 0;
}
