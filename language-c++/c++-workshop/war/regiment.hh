#pragma once

#include "soldier.hh"

class Regiment
{
public:
    Regiment()
        : soldiers_()
    {}

    void join_by(Regiment& r);
    size_t count() const;
    void add_soldier(Soldier* s);
    void print_state() const;
    void scream() const;

protected:
    std::vector<Soldier*> soldiers_;
};
