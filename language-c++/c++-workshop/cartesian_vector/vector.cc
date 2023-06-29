#include "vector.hh"

Vector operator+(const Vector& lhs, const Vector& vect)
{
    return Vector{ lhs.x + vect.x, lhs.y + vect.y };
}

Vector operator-(const Vector& lhs, const Vector& vect)
{
    return Vector{ lhs.x - vect.x, lhs.y - vect.y };
}

int operator*(const Vector& lhs, const Vector& vect)
{
    auto res = lhs.x * vect.x + lhs.y * vect.y;
    return res;
}

Vector operator*(const Vector& lhs, int scalar)
{
    return Vector{ lhs.x * scalar, lhs.y * scalar };
}

Vector operator*(int scalar, const Vector& lhs)
{
    auto res = operator*(lhs, scalar);
    return res;
}

Vector& Vector::operator+=(const Vector& rhs)
{
    this->x = this->x + rhs.x;
    this->y = this->y + rhs.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
    this->x = this->x - rhs.x;
    this->y = this->y - rhs.y;
    return *this;
}

Vector& Vector::operator*=(int scalar)
{
    this->x = this->x * scalar;
    this->y = this->y * scalar;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector& vect)
{
    os << "{" << vect.x << "," << vect.y << "}";
    return os;
}
