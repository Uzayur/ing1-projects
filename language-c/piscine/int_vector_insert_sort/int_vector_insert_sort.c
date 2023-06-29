#include "int_vector_insert_sort.h"

#include <stddef.h>

static struct int_vector swap(struct int_vector vec, size_t i, size_t j)
{
    int index_i = vec.data[i];
    int index_j = vec.data[j];

    vec.data[i] = index_j;
    vec.data[j] = index_i;

    return vec;
}

struct int_vector int_vector_insert_sort(struct int_vector vec)
{
    for (size_t i = 1; i < vec.size; i++)
    {
        while (vec.data[i] < vec.data[i - 1])
        {
            vec = swap(vec, i, i - 1);
            i--;
            if (i == 0)
                break;
        }
    }
    return vec;
}
