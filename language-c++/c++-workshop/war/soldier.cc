#include "soldier.hh"

void Soldier::attack(Soldier& s)
{
    s.health_ -= this->damage_;
}

void Soldier::print_state() const
{
    std::cout << "I have " << this->health_ << " health points.\n";
}

void Soldier::scream() const
{
    std::cout << this->scream_ << '\n';
}
