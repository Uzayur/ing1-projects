#include "merge-sort.hh"

#include <algorithm>
void merge_sort(iterator_type begin, iterator_type end)
{
    auto diff = end - begin;

    if (diff < 2)
        return;

    else if (diff == 2 && *(begin + 1) < *begin)
        std::iter_swap(begin, begin + 1);

    std::vector<int>::iterator pivot = begin + diff / 2;

    merge_sort(begin, pivot);
    merge_sort(pivot, end);

    std::inplace_merge(begin, pivot, end);
    return;
}
