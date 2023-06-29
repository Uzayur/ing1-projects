#pragma once

#include <iostream>

class Engine
{
public:
    Engine(int fuel);

    bool start();
    void use(int consumed);
    void stop() const;
    void fill(int fuel);

private:
    int fuel_;
};
