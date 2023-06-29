#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "functional_programming_advanced.h"

bool my_even(int a)
{
    if (a % 2 == 0)
        return false;
    return true;
}

void minus_one(int *array)
{
    *array -= 1;
}

void map(int *array, size_t len, void (*func)(int *))
{
    for (size_t i = 0; i < len; i++)
        func(array + i);
}

void print_even(int *array, size_t len)
{
    map(array, len, minus_one);

    int *out_array;
    size_t out_array_len = filter(array, len, &out_array, my_even);

    for (size_t i = 0; i < out_array_len; i++)
        printf("%d\n", out_array[i] + 1);

    free(out_array);
}
