#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
        return 1;

    char times = *argv[argc - 1];

    for (int i = 0; i < times - '0'; i++)
        puts(argv[argc - 2]);
    return 0;
}
