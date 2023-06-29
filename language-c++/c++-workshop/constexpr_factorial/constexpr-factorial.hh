#pragma once

constexpr unsigned long long factorial(unsigned int n)
{
    if (n < 2)
        return 1;
    return n >= 2 ? n * factorial(n - 1) : 1;
}
