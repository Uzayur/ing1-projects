#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "exist.hh"

int main()
{
    std::vector<char> v = { 'a', 'b', 'a', 'b', 'c', 'd', 'a' };
    auto exist = Exist<char>();
    auto last = std::remove_if(v.begin(), v.end(), std::ref(exist));
    v.erase(last, v.end());
    for (auto c : v)
        std::cout << c;
    std::cout << std::endl;
}
