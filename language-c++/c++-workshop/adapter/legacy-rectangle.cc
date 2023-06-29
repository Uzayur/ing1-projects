#include "legacy-rectangle.hh"

#include <cmath>

LegacyRectangle::LegacyRectangle(int x1, int y1, int x2, int y2)
    : x1_(x1)
    , y1_(y1)
    , x2_(x2)
    , y2_(y2)
{}

unsigned LegacyRectangle::compute_area() const
{
    return std::abs(x1_ - x2_) * std::abs(y1_ - y2_);
}

int LegacyRectangle::x1_get() const
{
    return x1_;
}

int LegacyRectangle::x2_get() const
{
    return x2_;
}

int LegacyRectangle::y1_get() const
{
    return y1_;
}

int LegacyRectangle::y2_get() const
{
    return y2_;
}
