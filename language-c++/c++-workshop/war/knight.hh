#pragma once

#include "soldier.hh"

class Knight : public Soldier
{
public:
    Knight()
    {
        health_ = 20;
        damage_ = 5;
        scream_ = "Be quick or be dead!";
    }
};
