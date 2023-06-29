#include "find-optional.hh"

#include <iostream>

std::optional<std::size_t> find_optional(const std::vector<int>& vect,
                                         int value)
{
    size_t index = -1;

    for (auto value_vect : vect)
    {
        if (value_vect == value)
        {
            return index + 1;
        }
        index++;
    }
    return std::nullopt;
}
