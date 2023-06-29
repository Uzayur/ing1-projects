#include "is-numerical.hh"

#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    std::cout << is_numerical<int>::value << '\n'; // must be true
    std::cout << is_numerical<float>::value << '\n'; // must be true
    std::cout << is_numerical<char>::value << '\n'; // must be true
    std::cout << is_numerical<std::string>::value << '\n'; // must be false

    return 0;
}
