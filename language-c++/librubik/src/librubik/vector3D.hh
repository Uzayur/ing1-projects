#pragma once

#include <ostream>

namespace rubik
{
    template <typename T>
    class Vector3D
    {
    public:
        Vector3D(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {}

        friend std::ostream& operator<<(std::ostream& os, const Vector3D& v)
        {
            os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
            return os;
        }

        bool operator==(const Vector3D& other)
        {
            return x == other.x and y == other.y and z == other.z;
        }

        bool operator!=(const Vector3D& other)
        {
            return x != other.x or y != other.y or z != other.z;
        }

        T x;
        T y;
        T z;
    };
} // namespace rubik
