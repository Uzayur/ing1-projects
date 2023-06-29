#include <stdio.h>

void resol_hanoi(unsigned n, int lft_tow, int md_tow, int rgt_tow)
{
    if (n != 0)
    {
        resol_hanoi(n - 1, lft_tow, rgt_tow, md_tow);
        putchar(lft_tow + 48);
        putchar(45);
        putchar(62);
        putchar(rgt_tow + 48);
        putchar(10);
        resol_hanoi(n - 1, md_tow, lft_tow, rgt_tow);
    }
    return;
}

void hanoi(unsigned n)
{
    resol_hanoi(n, 1, 2, 3);
    return;
}
