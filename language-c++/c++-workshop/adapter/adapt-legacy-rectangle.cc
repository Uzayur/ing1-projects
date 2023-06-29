#include "adapt-legacy-rectangle.hh"

#include <iostream>

AdaptLegacyRectangle::AdaptLegacyRectangle(LegacyRectangle& rect)
    : rect_(rect)
{}

AdaptLegacyRectangle::~AdaptLegacyRectangle()
{}

void AdaptLegacyRectangle::print() const
{
    std::cout << "x: " << this->rect_.x1_get() << " y: " << this->rect_.y1_get()
              << '\n'
              << "height: ";

    std::cout << abs(this->rect_.y1_get() - this->rect_.y2_get());

    std::cout << '\n'
              << "width: " << abs(this->rect_.x1_get() - this->rect_.x2_get())
              << '\n';
}

unsigned AdaptLegacyRectangle::area() const
{
    auto res1 = abs(this->rect_.x1_get() - this->rect_.x2_get());
    auto res2 = abs(this->rect_.y1_get() - this->rect_.y2_get());

    return res1 * res2;
}
