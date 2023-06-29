#include <iostream>

#include "stack.hh"

int main()
{
    Stack<int> stack = Stack<int>();
    stack += 1;
    stack += 2;
    std::cout << stack << std::endl;
    stack.pop();
    stack.pop();
    stack.pop();
}
