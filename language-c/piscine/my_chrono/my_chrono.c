#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./my_chrono <time>\n");
        return 1;
    }

    int secondes = argv[1][0];

    alarm(secondes);

    struct signification sa;

    sigaction(SIGALRM, &sa, NULL);

    return 0;
}
