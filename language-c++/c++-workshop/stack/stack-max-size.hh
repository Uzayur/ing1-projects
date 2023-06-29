#pragma once

#include <exception>
#include <sstream>
#include <string>

class StackMaxSize : public std::exception
{
public:
    const char* what() const noexcept;

private:
    std::string msg_ = "Unable to push, stack max size reached.";
};
