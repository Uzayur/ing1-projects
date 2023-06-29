#pragma once

#include <iostream>

namespace rubik
{
    enum class Color
    {
        WHITE,
        YELLOW,
        GREEN,
        BLUE,
        RED,
        ORANGE,
        NONE
    };

    inline std::ostream& operator<<(std::ostream& os, const Color& color)
    {
        switch (color)
        {
        case Color::WHITE:
            os << 'W';
            break;
        case Color::YELLOW:
            os << 'Y';
            break;
        case Color::GREEN:
            os << 'G';
            break;
        case Color::BLUE:
            os << 'B';
            break;
        case Color::RED:
            os << 'R';
            break;
        case Color::ORANGE:
            os << 'O';
            break;
        case Color::NONE:
            os << 'X';
            break;
        }
        return os;
    }
} // namespace rubik
