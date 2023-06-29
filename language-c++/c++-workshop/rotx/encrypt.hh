#pragma once

#include <string>

class Encrypt
{
public:
    Encrypt(const std::string& input)
        : input_(input)
    {}

    virtual void process() const = 0;

protected:
    std::string input_;
};
