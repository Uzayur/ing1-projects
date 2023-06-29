#include "closer-to.hh"

CloserTo::CloserTo(int i)
    : i_(i)
{}

bool CloserTo::operator()(const int& a, const int& b) const
{
    int res1 = a - i_;
    if (res1 <= 0)
        res1 = i_ - a;

    int res2 = b - i_;
    if (res2 <= 0)
        res2 = i_ - b;

    if (res1 != res2)
        return res2 > res1;
    return b > a;
}
