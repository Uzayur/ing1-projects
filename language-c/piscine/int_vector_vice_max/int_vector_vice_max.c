#include "int_vector_vice_max.h"

#include <stddef.h>

int int_vector_vice_max(const struct int_vector vec)
{
    int vice_index = 0;
    int max_index = 1;

    if (vec.data[0] > vec.data[1])
    {
        vice_index = 1;
        max_index = 0;
    }
    for (size_t i = 2; i < vec.size; i++)
    {
        if (vec.data[i] > vec.data[max_index])
        {
            vice_index = max_index;
            max_index = i;
        }
        else if (vec.data[i] > vec.data[vice_index])
            vice_index = i;
    }
    return vec.data[vice_index];
}
