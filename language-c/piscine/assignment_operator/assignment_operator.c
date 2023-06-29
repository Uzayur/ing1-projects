#include <stddef.h>

void plus_equal(int *a, int *b)
{
    if (a == NULL || b == NULL)
        return;

    int sum = *a + *b;
    *a = sum;
    return;
}

void minus_equal(int *a, int *b)
{
    if (a == NULL || b == NULL)
        return;

    int minus = *a - *b;
    *a = minus;
    return;
}

void mult_equal(int *a, int *b)
{
    if (a == NULL || b == NULL)
        return;

    int mult = (*a) * (*b);
    *a = mult;
    return;
}

int div_equal(int *a, int *b)
{
    if (b == NULL || a == NULL || *b == 0)
        return 0;
    else
    {
        int euclidien_division = (*a) / (*b);
        int rest = (*a) - euclidien_division * (*b);
        *a = euclidien_division;
        return rest;
    }
}
