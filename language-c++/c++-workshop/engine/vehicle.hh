#pragma once

#include <string>

#include "engine.hh"

class Vehicle
{
public:
    Vehicle(const std::string& model, int fuel);

    bool start();
    void stop();
    void cruise(int fuel);
    void fill(int fuel);

    virtual void change_tires() const = 0;

protected:
    const std::string model_;
    Engine engine_;
};
