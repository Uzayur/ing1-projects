#include <iostream>

template <int i, int j>
struct Foo
{
    void print()
    {
        std::cout << "Foo<" << i << ", " << j << ">\n";
    }
};

template <>
struct Foo<2, 4>
{
    void print()
    {
        std::cout << "Foo<" << 4 << ", " << 2 << ">\n";
    }
};

int main()
{
    Foo<2, 3> f1;
    Foo<2, 4> f2;
    f1.print(); // Displays: Foo<2, 3>
    f2.print(); // Displays: Foo<4, 2>
}
