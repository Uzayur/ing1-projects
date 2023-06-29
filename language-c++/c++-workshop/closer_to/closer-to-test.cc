#include <algorithm>
#include <iostream>
#include <vector>

#include "closer-to.hh"

void print_elt(int i)
{
    std::cout << ' ' << i;
}

int main()
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 5 };

    std::cout << "Unsorted vector:";
    std::for_each(v.begin(), v.end(), print_elt);
    std::cout << '\n';

    auto n = 3;

    std::sort(v.begin(), v.end(), CloserTo(n));

    std::cout << "Sorted vector closed to " << n << ':';
    std::for_each(v.begin(), v.end(), print_elt);
    std::cout << '\n';

    return 0;
}
