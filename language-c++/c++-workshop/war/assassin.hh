#pragma once

#include "soldier.hh"

class Assassin : public Soldier
{
public:
    Assassin()
    {
        health_ = 10;
        damage_ = 9;
        scream_ = "Out of the shadows!";
    }
};
