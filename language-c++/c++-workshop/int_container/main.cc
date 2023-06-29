#include "int-container.hh"

int main()
{
    MyIntContainer c = MyIntContainer(10);
    c.print();

    if (c.is_sorted())
        std::cout << "The array is sorted" << '\n';
    else
        std::cout << "The array is not sorted" << '\n';

    c.sort();
    c.print();

    if (c.is_sorted())
        std::cout << "The array is sorted" << '\n';
    else
        std::cout << "The array is not sorted" << '\n';

    return 0;
}
