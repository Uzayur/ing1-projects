#include "regiment.hh"

void Regiment::join_by(Regiment& r)
{
    for (size_t k = 0; k < r.soldiers_.size(); ++k)
        soldiers_.push_back(r.soldiers_[k]);

    r.soldiers_.clear();
}

size_t Regiment::count() const
{
    return soldiers_.size();
}

void Regiment::add_soldier(Soldier* s)
{
    soldiers_.push_back(s);
}

void Regiment::print_state() const
{
    for (size_t k = 0; k < soldiers_.size(); ++k)
    {
        soldiers_[k]->print_state();
    }
}

void Regiment::scream() const
{
    for (size_t k = 0; k < soldiers_.size(); ++k)
    {
        soldiers_[k]->scream();
    }
}
