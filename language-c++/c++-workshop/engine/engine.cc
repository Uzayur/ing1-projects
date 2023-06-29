#include "engine.hh"

Engine::Engine(int fuel)
    : fuel_(fuel)
{}

bool Engine::start()
{
    if (fuel_ == 0)
        return false;

    fuel_ -= 1;
    std::cout << "Engine starts with " << fuel_ << " units of fuel\n";
    return true;
}

void Engine::use(int consumed)
{
    int new_fuel = consumed;

    if (fuel_ <= consumed)
    {
        new_fuel = fuel_;
        fuel_ = 0;
    }
    else
        fuel_ -= consumed;

    std::cout << "Engine uses " << new_fuel << " fuel units\n";
}

void Engine::stop() const
{
    std::cout << "Stop Engine\n";
}

void Engine::fill(int fuel)
{
    fuel_ += fuel;
    std::cout << "Engine now has " << fuel_ << " fuel units\n";
}
