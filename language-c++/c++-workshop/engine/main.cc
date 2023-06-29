#include <iostream>

#include "motor-cycle.hh"
#include "motor-truck.hh"

int main()
{
    MotorTruck mt("Ford", 10, 6);
    MotorCycle mc("Suzuki");
    mt.start();
    mt.cruise(4);
    mt.fill(2);
    mt.cruise(15);
    mt.fill(4);
    mt.stop();
    mt.change_tires();
    mc.start();
    mc.fill(2);
    mc.cruise(15);
    mc.fill(4);
    mc.stop();
    mc.change_tires();
    return 0;
}
