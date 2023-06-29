#pragma once

#include <iostream>
#include <vector>

template <typename T>

bool palindrome(std::vector<T> vector)
{
    auto size = vector.size() - 1;

    for (size_t k = 0; k < vector.size() / 2; k++)
    {
        if (vector[k] != vector[size - k])
            return false;
    }
    return true;
}
