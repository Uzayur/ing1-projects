#include "cube.hh"

#include "move.hh"

namespace rubik
{
    bool check_line(std::string line)
    {
        std::stringstream test;
        test.str(line);

        std::string token;

        int count = 0;
        while (test >> token)
            count++;

        int par = 0;
        int vir = 0;
        for (size_t k = 0; k < line.size(); k++)
        {
            if (line[k] == ',')
                vir++;
            if (line[k] == '(' or line[k] == ')')
                par++;
        }

        if (par != 4 or vir != 4)
            return false;

        return count == 2 or count == 0;
    }

    Color get_color(char c)
    {
        switch (c)
        {
        case 'W':
            return Color::WHITE;
        case 'Y':
            return Color::YELLOW;
        case 'G':
            return Color::GREEN;
        case 'B':
            return Color::BLUE;
        case 'R':
            return Color::RED;
        case 'O':
            return Color::ORANGE;
        case 'X':
            return Color::NONE;
        }
        return Color::NONE;
    }

    Cube Cube::from_stream(std::istream& is)
    {
        Cube cube;
        cube.pieces_.clear();

        std::string line;

        while (std::getline(is, line, is.widen('\n')))
        {
            if (!check_line(line))
                throw std::invalid_argument("invalid syntax");

            int x;
            int y;
            int z;

            Color cx;
            Color cy;
            Color cz;

            int begin = 1;
            int end = line.find(',', begin);
            x = std::stoi(line.substr(1, end - 1), 0, 10);

            begin = end + 1;
            end = line.find(',', begin);
            y = std::stoi(line.substr(begin, end - 1), 0, 10);

            begin = end + 1;
            end = line.find(')', begin);
            z = std::stoi(line.substr(begin, end - 1), 0, 10);

            begin = line.find('(', end) + 1;
            cx = get_color(line[begin]);
            cy = get_color(line[begin + 2]);
            cz = get_color(line[begin + 4]);

            cube.pieces_.push_back(Piece{ { x, y, z }, { cx, cy, cz } });
        }

        return cube;
    }

    std::vector<Piece>::iterator Cube::begin()
    {
        return pieces_.begin();
    }

    std::vector<Piece>::iterator Cube::end()
    {
        return pieces_.end();
    }

    std::vector<Piece>::const_iterator Cube::begin() const
    {
        return pieces_.cbegin();
    }

    std::vector<Piece>::const_iterator Cube::end() const
    {
        return pieces_.cend();
    }

    Piece Cube::find_piece(Vector3D<int> coords) const
    {
        for (auto& piece : pieces_)
        {
            auto x = piece.coords.x;
            auto y = piece.coords.y;
            auto z = piece.coords.z;

            if (coords.x == x and coords.y == y and coords.z == z)
                return piece;
        }
        throw std::invalid_argument("Cannot find the piece");
    }

    Piece Cube::find_piece(Vector3D<Color> colors) const
    {
        for (auto& piece : pieces_)
        {
            Color pcx = piece.colors.x;
            Color pcy = piece.colors.y;
            Color pcz = piece.colors.z;

            if (colors == Vector3D(pcx, pcy, pcz))
                return piece;

            if (colors == Vector3D(pcx, pcz, pcy))
                return piece;

            if (colors == Vector3D(pcy, pcx, pcz))
                return piece;

            if (colors == Vector3D(pcy, pcz, pcx))
                return piece;

            if (colors == Vector3D(pcz, pcy, pcx))
                return piece;

            if (colors == Vector3D(pcz, pcx, pcy))
                return piece;
        }
        throw std::invalid_argument("Cannot find the color piece");
    }

    void Cube::do_move(Move move)
    {
        if (std::holds_alternative<Face>(move.mvt))
        {
            auto mvt = std::get<Face>(move.mvt);
            for (Piece& p : pieces_)
            {
                if (mvt == Face::FRONT and p.coords.x == 1)
                {
                    if (move.is_double)
                        p.do_move(mvt, move.dir);
                    p.do_move(mvt, move.dir);
                }

                if (mvt == Face::BACK and p.coords.x == -1)
                {
                    if (move.is_double)
                        p.do_move(mvt, move.dir);
                    p.do_move(mvt, move.dir);
                }

                if (mvt == Face::RIGHT and p.coords.y == 1)
                {
                    if (move.is_double)
                        p.do_move(mvt, move.dir);
                    p.do_move(mvt, move.dir);
                }

                if (mvt == Face::LEFT and p.coords.y == -1)
                {
                    if (move.is_double)
                        p.do_move(mvt, move.dir);
                    p.do_move(mvt, move.dir);
                }

                if (mvt == Face::UP and p.coords.z == 1)
                {
                    if (move.is_double)
                        p.do_move(mvt, move.dir);
                    p.do_move(mvt, move.dir);
                }

                if (mvt == Face::DOWN and p.coords.z == -1)
                {
                    if (move.is_double)
                        p.do_move(mvt, move.dir);
                    p.do_move(mvt, move.dir);
                }
            }
        }
        else
        {
            auto mvt = std::get<Axis>(move.mvt);
            for (Piece& p : pieces_)
            {
                if (move.is_double)
                    p.do_move(mvt, move.dir);
                p.do_move(mvt, move.dir);
            }
        }
    }

    void Cube::do_moves(std::vector<Move> moves)
    {
        for (auto& move : moves)
            do_move(move);
    }

    void Cube::undo_move(Move move)
    {
        Direction new_dir = Direction::CLOCKWISE;
        if (move.dir == Direction::CLOCKWISE)
            new_dir = Direction::ANTI_CLOCKWISE;

        auto new_move = Move(move.mvt, new_dir, move.is_double);
        do_move(new_move);
    }

    void Cube::undo_moves(std::vector<Move> moves)
    {
        for (int k = moves.size() - 1; k >= 0; k--)
            undo_move(moves[k]);
    }
} // namespace rubik
