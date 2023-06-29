#pragma once

#include <cmath>
#include <iostream>

template <typename A, typename B, typename F>
void my_foreach(A begin, B end, F function)
{
    for (auto i = begin; i != end; i++)
        function(*i);
}
