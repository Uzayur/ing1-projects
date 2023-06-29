#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

static char *my_itoa(int value, char *s)
{
    int index = 0;

    if (value < 0)
    {
        s[index] = '-';
        value = -value;
        index++;
    }

    int index_pui = 10;

    while (value / index_pui > 9)
        index_pui *= 10;

    while (value > 9)
    {
        s[index] = '0' + value / index_pui;
        value = value % index_pui;
        index_pui /= 10;
        index++;
    }
    s[index] = '0' + value;
    s[index + 1] = '\0';
    return s;
}

static void print_preorder(int *array, size_t size, size_t index)
{
    if (index >= size)
        return;
    else
    {
        char *s = malloc(sizeof(char) * 4);
        s = my_itoa(array[index], s);
        if (!index)
        {
            int ind = 0;
            while (s[ind] != '\0')
                putchar(s[ind++]);
        }
        else
        {
            putchar(' ');
            int ind = 0;
            while (s[ind] != '\0')
                putchar(s[ind++]);
        }
        free(s);
        print_preorder(array, size, 2 * index + 1);
        print_preorder(array, size, 2 * index + 2);
    }
}

void print_heap(const struct heap *heap)
{
    print_preorder(heap->array, heap->size, 0);
    putchar('\n');
}
