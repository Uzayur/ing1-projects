#include <iostream>

#include "pair.hh"

int main()
{
    Pair<int, char> p1(69, 'f');
    Pair<int, char> p2(68, 'a');
    Pair<int, char> p3(69, 'f');

    if (p1 == p2)
        std::cout << "p1 and p2 are equal\n";
    if (p2 != p3)
        std::cout << "p2 and p3 are not equal\n";
    if (p1 == p3)
        std::cout << "p1 and p3 are equal\n";
    if (p1 != p3)
        std::cout << "p1 and p3 are not equal\n";
}
