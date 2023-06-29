#include "piece.hh"

#include "matrix3D.hh"

namespace rubik
{
    Piece::Type Piece::get_type()
    {
        size_t count = 0;
        if (colors.x == Color::NONE)
            count++;
        if (colors.y == Color::NONE)
            count++;
        if (colors.z == Color::NONE)
            count++;

        switch (count)
        {
        case 0:
            return Piece::Type::CORNER;
        case 1:
            return Piece::Type::EDGE;
        case 2:
            return Piece::Type::CENTER;
        case 3:
            return Piece::Type::NONE;
        }
        return Piece::Type::NONE;
    }

    void swap_yz(Vector3D<Color>& colors)
    {
        auto tmp = colors.y;
        colors.y = colors.z;
        colors.z = tmp;
    }

    void swap_xz(Vector3D<Color>& colors)
    {
        auto tmp = colors.x;
        colors.x = colors.z;
        colors.z = tmp;
    }

    void swap_xy(Vector3D<Color>& colors)
    {
        auto tmp = colors.x;
        colors.x = colors.y;
        colors.y = tmp;
    }

    void Piece::do_move(Face face, Direction dir)
    {
        auto sens = 1;
        if (dir == Direction::ANTI_CLOCKWISE)
            sens = -1;

        std::array<std::array<int, 3>, 3> rx = {
            { { 1, 0, 0 }, { 0, 0, -(sens) }, { 0, sens, 0 } }
        };

        std::array<std::array<int, 3>, 3> ry = {
            { { 0, 0, sens }, { 0, 1, 0 }, { -(sens), 0, 0 } }
        };

        std::array<std::array<int, 3>, 3> rz = {
            { { 0, -(sens), 0 }, { sens, 0, 0 }, { 0, 0, 1 } }
        };

        auto Rx = Matrix3D<int>{ rx };
        auto Ry = Matrix3D<int>{ ry };
        auto Rz = Matrix3D<int>{ rz };

        if (face == Face::FRONT)
        {
            Rx.transpose();
            this->coords = Rx * this->coords;
            swap_yz(this->colors);
            Rx.transpose();
        }
        if (face == Face::BACK)
        {
            this->coords = Rx * this->coords;
            swap_yz(this->colors);
        }
        if (face == Face::RIGHT)
        {
            Ry.transpose();
            this->coords = Ry * this->coords;
            swap_xz(this->colors);
            Ry.transpose();
        }
        if (face == Face::LEFT)
        {
            this->coords = Ry * this->coords;
            swap_xz(this->colors);
        }
        if (face == Face::UP)
        {
            Rz.transpose();
            this->coords = Rz * this->coords;
            swap_xy(this->colors);
            Rz.transpose();
        }
        if (face == Face::DOWN)
        {
            this->coords = Rz * this->coords;
            swap_xy(this->colors);
        }
    }

    void Piece::do_move(Axis axis, Direction dir)
    {
        if (axis == Axis::X)
            do_move(Face::RIGHT, dir);

        if (axis == Axis::Y)
            do_move(Face::UP, dir);

        if (axis == Axis::Z)
            do_move(Face::FRONT, dir);
    }

} // namespace rubik
