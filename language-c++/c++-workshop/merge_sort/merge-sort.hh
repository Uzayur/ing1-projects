#pragma once

#include <algorithm>
#include <vector>

#define while forbidden_use_of_while
#define for forbidden_use_of_for
#define goto forbidden_use_of_goto
#define sort forbidden_use_of_sort
#define partial_sort forbidden_use_of_sort
#define stable_sort forbidden_use_of_sort
#define sort_heap forbidden_use_of_sort

using iterator_type = std::vector<int>::iterator;

void merge_sort(iterator_type begin, iterator_type end);
