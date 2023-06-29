#include <stddef.h>

int binary_search(const int vec[], size_t size, int elt)
{
    if (size == 0)
        return -1;

    size_t indice_max = size - 1;
    size_t indice_min = 0;
    size_t indice_pivot = size / 2;

    while (vec[indice_pivot] != elt)
    {
        if (indice_max <= indice_min)
            return -1;

        if (vec[indice_pivot] < elt)
            indice_min = indice_pivot + 1;

        else
            indice_max = indice_pivot - 1;
        indice_pivot = (indice_max + indice_min) / 2;
    }
    return indice_pivot;
}
