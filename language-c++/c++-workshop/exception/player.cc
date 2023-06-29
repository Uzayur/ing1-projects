#include "player.hh"

Player::Player(const std::string& name, unsigned int age)
    : name_(name)
    , age_(age)
{
    if (name.size() == 0)
        throw InvalidArgumentException("Name can't be empty.");

    else if (age > 150)
        throw InvalidArgumentException("Sorry gramp, too old to play.");
}
