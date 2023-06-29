#include "read-info.hh"

#include <fstream>
#include <sstream>

DirectoryInfo* read_info(std::ifstream& file)
{
    std::string token;

    std::string name;
    std::string size;
    std::string rights;
    std::string owner;

    std::string str_line;

    std::getline(file, str_line, file.widen('\n'));

    std::stringstream line;
    line.str(str_line);

    if (line >> token)
        name = token;
    else
        return nullptr;

    if (line >> token)
        size = token;
    else
        return nullptr;

    if (line >> token)
        rights = token;
    else
        return nullptr;

    if (line >> token)
        owner = token;
    else
        return nullptr;

    if (line.rdbuf()->in_avail())
        return nullptr;

    long int right;
    for (size_t k = 0; k < rights.size(); k++)
    {
        if (!isdigit(rights[k]))
            return nullptr;
    }

    for (size_t k = 0; k < size.size(); k++)
    {
        if (!isdigit(size[k]))
            return nullptr;
    }

    if (rights.find('8') != std::string::npos
        or rights.find('9') != std::string::npos)
        return nullptr;

    else
        right = std::stoi(rights, 0, 8);

    auto size_int = std::stoi(size, 0, 10);

    auto new_dir = new DirectoryInfo(name, size_int, right, owner);
    return new_dir;
}
