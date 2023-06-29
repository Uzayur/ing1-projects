#include <stdio.h>

void display_square(int width)
{
    if (width <= 0)
        return;
    else if (width == 1)
    {
        putchar(42);
        putchar(10);
        return;
    }

    if (width % 2 == 0)
        width++;

    for (int i = 0; i < width; i++)
        putchar(42);
    putchar(10);

    int line_number = (width - 3) / 2;
    for (int i = 0; i < line_number; i++)
    {
        putchar(42);
        for (int i = 0; i < width - 2; i++)
            putchar(32);
        putchar(42);
        putchar(10);
    }

    for (int i = 0; i < width; i++)
        putchar(42);
    putchar(10);

    return;
}
