#include <iostream>

#include "ref-swap.hh"

int main()
{
    int a = 3;
    int b = 19;

    std::cout << "Before: a = " << a << ", b = " << b << '\n';
    swap(a, b);
    std::cout << "After: a = " << a << ", b = " << b << '\n';

    std::cout << "Before: a = " << a << ", b = " << b << '\n';
    swap(a, b);
    std::cout << "After: a = " << a << ", b = " << b << '\n';
}
