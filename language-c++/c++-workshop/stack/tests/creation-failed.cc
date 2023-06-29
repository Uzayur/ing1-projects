#include <iostream>
#include <stdexcept>
#include <vector>

#include "stack-creation-failed.hh"
#include "stack.hh"

namespace std
{
    template <>
    void std::vector<int>::reserve(size_t)
    {
        throw std::length_error("");
    }
} // namespace std

int main()
{
    std::vector<int> v;
    try
    {
        auto A = Stack<int>(2);
        A << 1;
    }
    catch (const StackCreationFailed& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
