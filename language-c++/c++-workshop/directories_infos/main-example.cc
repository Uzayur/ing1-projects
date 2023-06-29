// main-example.cc

#include <fstream>
#include <iomanip>
#include <iostream>

#include "directory-info.hh"
#include "read-info.hh"

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    auto file = std::ifstream(argv[1]);

    while (true)
    {
        auto dir_info = read_info(file);

        if (dir_info == nullptr)
            break;

        std::cout << dir_info->get_name() << '|' << dir_info->get_size() << '|'
                  << std::oct << dir_info->get_rights() << std::dec << '|'
                  << dir_info->get_owner() << '\n';

        delete dir_info;
    }
}
