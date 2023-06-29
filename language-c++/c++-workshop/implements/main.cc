#include <iostream>
#include <sstream>

#include "implements.hh"

template <typename T, typename T2 = T>
static void test()
{
    std::ostringstream type;
    type << '<' << typeid(T).name();
    if (typeid(T) != typeid(T2))
        type << ", " << typeid(T2).name();
    type << ">";

    std::cout << "impl_basic_op" << type.str() << " = "
              << impl_basic_op<T, T2> << '\n';
    std::cout << "impl_modulo" << type.str() << " = "
              << impl_modulo<T, T2> << '\n';
    std::cout << "impl_bitwise_op" << type.str() << " = "
              << impl_bitwise_op<T, T2> << '\n';
    std::cout << "impl_arith_op" << type.str() << " = "
              << impl_arith_op<T, T2> << '\n';
}

int main()
{
    std::cout << std::boolalpha;
    test<int>();
    std::cout << '\n';
    test<bool, char>();
    std::cout << '\n';
    test<float>();
    std::cout << '\n';
    test<float, int>();
    return 0;
}
