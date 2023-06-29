#include <stdio.h>

int main(void)
{
    putchar(97);
    for (int i = 98; i < 123; i++)
    {
        putchar(32);
        putchar(i);
    }
    putchar(10);
    return 0;
}
