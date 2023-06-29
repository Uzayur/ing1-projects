#include "ref-swap.hh"

void swap(int& a, int& b)
{
    auto tmp = a;
    a = b;
    b = tmp;
}
