#pragma once

#include "vehicle.hh"

class MotorTruck : public Vehicle
{
public:
    MotorTruck(const std::string& model, int fuel, size_t nb_tires);

    void change_tires() const override;

private:
    size_t nb_tires_;
};
