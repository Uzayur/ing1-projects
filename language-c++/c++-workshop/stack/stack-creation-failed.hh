#pragma once

#include <exception>
#include <sstream>
#include <string>

class StackCreationFailed : public std::exception
{
public:
    StackCreationFailed(const std::string& msg);
    const char* what() const noexcept;

private:
    std::string msg_;
};
