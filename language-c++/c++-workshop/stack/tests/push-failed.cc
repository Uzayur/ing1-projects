#include <iostream>

#include "stack.hh"

int main()
{
    Stack<int> stack = Stack<int>(3);
    stack += 1;
    std::cout << stack << std::endl;
    stack += 2;
    std::cout << stack << std::endl;
    stack += 3;
    std::cout << stack << std::endl;
    stack += 4;
}
