#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    DIR *dir;
    if (argc == 1)
        dir = opendir("./");
    else
        dir = opendir(argv[1]);

    if (dir == NULL)
    {
        fprintf(stderr, "simple_ls: %s: No such file or directory\n", argv[1]);
        return 1;
    }

    struct dirent *directory;
    while ((directory = readdir(dir)))
    {
        if (directory->d_name[0] != '.')
            printf("%s\n", directory->d_name);
    }

    closedir(dir);
    return 0;
}
