#pragma once

#include <iostream>
#include <string>
#include <vector>

class Soldier
{
public:
    Soldier()
        : health_(15)
        , damage_(3)
        , scream_("No pity for losers!")
    {}

    void attack(Soldier& s);
    void print_state() const;
    void scream() const;

protected:
    int health_;
    int damage_;
    std::string scream_;
};
