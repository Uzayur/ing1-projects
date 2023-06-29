#include "int_vector_bubble_sort.h"

static struct int_vector swap(struct int_vector vec, size_t i, size_t j)
{
    int index_i = vec.data[i];
    int index_j = vec.data[j];

    vec.data[i] = index_j;
    vec.data[j] = index_i;

    return vec;
}

struct int_vector int_vector_bubble_sort(struct int_vector vec)
{
    if (vec.size == 0)
        return vec;

    size_t indicator = 0;
    while (indicator != vec.size - 1)
    {
        indicator = 0;
        for (size_t i = 0; i < vec.size - 1; i++)
        {
            if (vec.data[i] > vec.data[i + 1])
                vec = swap(vec, i, i + 1);
            else
                indicator += 1;
        }
    }
    return vec;
}
