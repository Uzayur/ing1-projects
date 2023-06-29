#include "builder.hh"

#include "components.hh"

Car Builder::get_car() const
{
    Car new_car;

    for (auto k = 0; k < 4; k++)
        new_car.wheels_[k] = get_wheel();

    new_car.engine_ = get_engine();
    new_car.body_ = get_body();

    return new_car;
}

std::unique_ptr<Wheel> JeepBuilder::get_wheel() const
{
    return std::unique_ptr<Wheel>(new Wheel(22));
}

std::unique_ptr<Engine> JeepBuilder::get_engine() const
{
    return std::unique_ptr<Engine>(new Engine(400));
}

std::unique_ptr<Body> JeepBuilder::get_body() const
{
    return std::unique_ptr<Body>(new Body("SUV"));
}

std::unique_ptr<Wheel> NissanBuilder::get_wheel() const
{
    return std::unique_ptr<Wheel>(new Wheel(16));
}

std::unique_ptr<Engine> NissanBuilder::get_engine() const
{
    return std::unique_ptr<Engine>(new Engine(85));
}

std::unique_ptr<Body> NissanBuilder::get_body() const
{
    return std::unique_ptr<Body>(new Body("hatchback"));
}
