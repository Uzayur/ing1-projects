#include <iostream>

#include "list.hh"

int main()
{
    List l = List();
    l.print(std::cout);
    std::cout << '\n';

    l.push_back(13);
    l.print(std::cout);
    std::cout << '\n';

    l.push_front(5);
    l.print(std::cout);
    std::cout << '\n';

    l.push_back(42);
    l.print(std::cout);
    std::cout << '\n';

    l.pop_back();
    l.print(std::cout);
    std::cout << '\n';

    l.push_back(42);
    l.print(std::cout);
    std::cout << '\n';

    l.pop_front();
    l.print(std::cout);
    std::cout << '\n';

    std::cout << "Nb elts: " << l.length() << '\n';
}
