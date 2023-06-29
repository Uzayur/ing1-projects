#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    argc++;
    int pid = fork();
    if (pid == 0)
        execlp("/bin/sh", "supershell", "-c", argv[1]);

    int wstatus;
    waitpid(pid, &wstatus, 0);
    printf("process exit status: %d\n", WEXITSTATUS(wstatus));

    return 0;
}
