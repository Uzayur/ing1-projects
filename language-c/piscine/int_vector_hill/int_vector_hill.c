#include "int_vector_hill.h"

#include <stddef.h>

int valid_hill(struct int_vector vec)
{
    size_t index = 0;
    while (index < vec.size)
    {
        if (vec.data[index] < 0)
            return -1;
        index++;
    }
    return 0;
}

int int_vector_hill(struct int_vector vec)
{
    if (vec.size == 0 || valid_hill(vec) == -1)
        return -1;
    else
    {
        size_t index = 0;
        size_t size = vec.size - 1;

        while (vec.data[index] <= vec.data[index + 1] && index < size)
            index++;
        while (vec.data[index] >= vec.data[index + 1] && index < size)
            index++;

        if (index != vec.size - 1)
            return -1;
        else
        {
            int hill_top = 0;
            for (size_t i = 0; i < vec.size; i++)
            {
                if (vec.data[i] > vec.data[hill_top])
                    hill_top = i;
            }
            return hill_top;
        }
    }
}
