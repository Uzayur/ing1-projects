#include "forward-multiplication.hh"

#include <iostream>
#include <string>

lambda_type create_lambda()
{
    std::function<std::function<int(int)>(int)> first_lambda = [](int a) {
        std::function<int(int)> second_lambda = [a](int b) { return b * a; };
        return second_lambda;
    };
    return first_lambda;
}
