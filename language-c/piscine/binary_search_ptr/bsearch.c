#include "bsearch.h"

#include <stddef.h>

int *binary_search(int *begin, int *end, int elt)
{
    if (begin == end)
        return begin;

    int *mid = begin + (end - begin - 1) / 2;

    while (*mid != elt)
    {
        if (*mid > elt)
            end = mid - 1;
        else if (*mid <= elt)
            begin = mid + 1;

        if (end == begin)
            return begin;
        else if (end - begin == 1)
        {
            if (*begin >= elt)
                return begin;
            return end;
        }
        mid = begin + (end - begin - 1) / 2;
    }
    return mid;
}
