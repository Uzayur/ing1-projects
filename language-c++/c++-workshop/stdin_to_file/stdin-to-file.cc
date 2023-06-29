#include "stdin-to-file.hh"

void stdin_to_file()
{
    std::ofstream file_out;
    file_out.open("file.out");

    std::string token;
    while (std::cin >> token)
    {
        file_out << token << "\n";
    }
}
