#include <stdlib.h>

void stdintail(unsigned int n);

int main(int argc, char *argv[])
{
    if (argc > 1)
        stdintail(atoi(argv[1]));
    return 0;
}
