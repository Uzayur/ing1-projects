#include "move.hh"

#include <sstream>

namespace rubik
{

    std::vector<Move> parse_moves(std::string input)
    {
        std::vector<Move> moves;

        std::stringstream stream;
        stream.str(input);

        std::string move_str;

        while (stream >> move_str)
        {
            if (move_str.size() >= 3)
                throw std::invalid_argument("Bad arguments");

            std::variant<Face, Axis> var;
            Direction dir = Direction::CLOCKWISE;
            bool is_double = false;

            char first = move_str[0];
            char second = move_str[1];

            if (first == 'R')
                var = Face::RIGHT;
            else if (first == 'L')
                var = Face::LEFT;
            else if (first == 'U')
                var = Face::UP;
            else if (first == 'D')
                var = Face::DOWN;
            else if (first == 'F')
                var = Face::FRONT;
            else if (first == 'B')
                var = Face::BACK;
            else if (first == 'x')
                var = Axis::X;
            else if (first == 'y')
                var = Axis::Y;
            else if (first == 'z')
                var = Axis::Z;
            else
                throw std::invalid_argument("Bad arguments");

            if (second == '2')
                is_double = true;
            else if (second == 39)
                dir = Direction::ANTI_CLOCKWISE;
            else if (second != '\0')
                throw std::invalid_argument("Bad arguments");

            auto new_move = Move(var, dir, is_double);
            moves.push_back(new_move);
        }
        return moves;
    }
} // namespace rubik
