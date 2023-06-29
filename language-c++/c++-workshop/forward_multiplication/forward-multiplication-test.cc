#include <iostream>
#include <string>

#include "forward-multiplication.hh"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " 'number' 'number'" << std::endl;
        return 1;
    }

    auto forward = create_lambda();
    auto lhs = std::stoi(argv[1]);
    auto rhs = std::stoi(argv[2]);

    auto f2 = forward(lhs);

    std::cout << forward(lhs)(rhs) << '\n';
    std::cout << f2(rhs) << std::endl;
}
