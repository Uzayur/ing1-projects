#include <iostream>

#include "word-count.hh"

int main()
{
    std::cout << word_count("file.in") << '\n';
    std::cout << word_count("fail.in") << '\n';
    return 0;
}
