// main-example.cc

#include <iostream>

#include "merge-sort.hh"

int main()
{
    auto vect = std::vector{ 8, -1, 3, 5, 0, 6 };
    std::cout << std::boolalpha << std::is_sorted(vect.begin(), vect.end())
              << '\n'; // false

    merge_sort(vect.begin(), vect.end());

    std::cout << std::boolalpha << std::is_sorted(vect.begin(), vect.end())
              << '\n'; // true
}
