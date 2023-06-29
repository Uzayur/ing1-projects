#include <iostream>

#include "parse-csv.hh"

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;
    try
    {
        auto v = parse_csv(std::string(argv[1]));
        std::cout << v[1][0] << '\n' << v[1][1] << '\n';
        for (size_t i = 0; i < v[2].size(); i++)
            std::cout << v[2][i];
        std::cout << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
