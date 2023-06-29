#pragma once

#include "invalid-argument.hh"

class Player
{
public:
    Player(const std::string& name, unsigned int age);

private:
    std::string name_;
    unsigned int age_;
};
