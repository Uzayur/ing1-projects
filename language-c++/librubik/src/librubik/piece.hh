#pragma once

#include <array>

#include "color.hh"
#include "move.hh"
#include "vector3D.hh"

namespace rubik
{
    class Piece
    {
    public:
        Vector3D<int> coords;
        Vector3D<Color> colors;

        enum Type
        {
            NONE,
            CENTER,
            EDGE,
            CORNER
        };

        Piece::Type get_type();

        friend std::ostream& operator<<(std::ostream& os, const Piece& p)
        {
            os << p.coords << ' ' << p.colors;
            return os;
        }

        bool operator==(const Piece& other)
        {
            return coords == other.coords and colors == other.colors;
        }

        bool operator<(const Piece& other)
        {
            if (coords.x < other.coords.x)
                return true;
            else if (coords.x > other.coords.x)
                return false;

            if (coords.y < other.coords.y)
                return true;
            else if (coords.y > other.coords.y)
                return false;

            return coords.z < other.coords.z;
        }

        bool operator!=(const Piece& other)
        {
            return coords != other.coords or colors != other.colors;
        }

        bool operator>(const Piece& other)
        {
            if (coords.x > other.coords.x)
                return true;
            else if (coords.x < other.coords.x)
                return false;

            if (coords.y > other.coords.y)
                return true;
            else if (coords.y < other.coords.y)
                return false;

            return coords.z > other.coords.z;
        }

        bool operator<=(const Piece& other)
        {
            return !(Piece(coords, colors) > other);
        }

        bool operator>=(const Piece& other)
        {
            return !(Piece(coords, colors) < other);
        }

        void do_move(Face face, Direction dir);
        void do_move(Axis axis, Direction dir);
    };
} // namespace rubik
