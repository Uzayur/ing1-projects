// vector-test.cc
#include <iostream>

#include "vector.hh"

int main()
{
    auto u = Vector{};
    auto v = Vector{ 4, 7 };
    auto t = Vector{ -1, 6 };

    std::cout << u + v << '\n'; // {4,7}
    u += Vector{ 1, 8 };
    std::cout << u << '\n'; // {1,8}
    t -= u;
    std::cout << t << '\n'; // {-2,-2}
    std::cout << t * 3 << '\n'; // {-6,-6}
    std::cout << u * v << '\n'; // 60

    return 0;
}
