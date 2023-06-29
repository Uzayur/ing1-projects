#include "unix-path.hh"

std::string UnixPath::to_string() const
{
    std::string path;

    for (auto elem : path_)
    {
        path.append("/");
        path.append(elem);
    }

    return path;
}
