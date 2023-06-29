#include "vehicle.hh"

Vehicle::Vehicle(const std::string& model, int fuel)
    : model_(model)
    , engine_(Engine(fuel))
{}

bool Vehicle::start()
{
    return engine_.start();
}

void Vehicle::stop()
{
    engine_.stop();
}

void Vehicle::cruise(int fuel)
{
    engine_.use(fuel);
}

void Vehicle::fill(int fuel)
{
    engine_.fill(fuel);
}
