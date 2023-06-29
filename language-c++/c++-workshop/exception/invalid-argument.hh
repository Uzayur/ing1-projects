#pragma once

#include <exception>
#include <string>

class InvalidArgumentException : public std::exception
{
public:
    InvalidArgumentException(const std::string& msg);

    virtual const char* what() const noexcept;

private:
    std::string msg_;
};
