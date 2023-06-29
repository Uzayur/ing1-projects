#pragma once

#include <ostream>

struct Vector
{
    Vector() = default;
    Vector(int init_x, int init_y)
        : x{ init_x }
        , y{ init_y }
    {}

    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(int scalar);

    int x = 0;
    int y = 0;
};

std::ostream& operator<<(std::ostream& os, const Vector& vect);

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);
Vector operator*(const Vector& lhs, int scalar);
Vector operator*(int scalar, const Vector& rhs);
int operator*(const Vector& lhs, const Vector& rhs);
