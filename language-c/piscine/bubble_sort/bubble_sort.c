#include <stddef.h>

void bubble_sort(int array[], size_t size)
{
    if (size == 0)
        return;

    size_t indicator = 0;
    while (indicator != size - 1)
    {
        indicator = 0;
        for (size_t i = 0; i < size - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                int transition = array[i];
                array[i] = array[i + 1];
                array[i + 1] = transition;
            }
            else
                indicator += 1;
        }
    }
    return;
}
