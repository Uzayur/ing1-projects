#include <iostream>
#include <string>

#include "libhello/hello.hh"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: /student <name>" << '\n';
        return 1;
    }

    say_hello(argv[1]);
    return 0;
}
