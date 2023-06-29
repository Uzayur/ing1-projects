#include "termcolor.hh"

int main()
{
    std::cout << termcolor::foreground::red << "nice,"
              << "still in red" << termcolor::foreground::blue << "blue"
              << std::endl;
    std::cout << "normal color\n";
    std::cout << termcolor::background::yellow << "pikachu\n";
    std::cout << '\n';
}
