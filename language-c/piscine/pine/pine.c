#include <stdio.h>

int pine(unsigned n)
{
    if (n < 3)
        return 1;

    for (unsigned int i = 1; i <= n; i++)
    {
        for (int c = n - 1 - i; c >= 0; c--)
            putchar(32);

        for (unsigned int e = 1; e < 2 * i; e++)
            putchar(42);

        putchar(10);
    }

    for (unsigned int p = 0; p < n / 2; p++)
    {
        for (unsigned int i = n; i > 1; --i)
            putchar(32);

        putchar(42);
        putchar(10);
    }
    return 0;
}
