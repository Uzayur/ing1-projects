#include <stddef.h>
#include <stdlib.h>

int *my_calloc(size_t size, int init)
{
    long unsigned int max = 2147483647;
    if (size == 0 || sizeof(init) * size > max)
        return NULL;
    else
    {
        int *ptr = malloc(sizeof(int) * size);
        for (size_t i = 0; i < size; i++)
            ptr[i] = init;
        return ptr;
    }
}
