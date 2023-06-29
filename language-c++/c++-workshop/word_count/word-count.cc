#include "word-count.hh"

#include <fstream>

ssize_t word_count(const std::string& filename)
{
    std::ifstream file_in;
    std::string token;

    file_in.open(filename);

    if (file_in.is_open())
    {
        auto count = 0;
        while (file_in >> token)
            count++;

        return count;
    }
    else
        return -1;
}
