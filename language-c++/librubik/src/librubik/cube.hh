#pragma once

#include <sstream>
#include <vector>

#include "piece.hh"

namespace rubik
{
    class Cube
    {
    public:
        Cube()
        {
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    for (int z = -1; z < 2; z++)
                    {
                        Color cx;
                        Color cy;
                        Color cz;

                        if (x == 1)
                            cx = Color::GREEN;
                        if (x == 0)
                            cx = Color::NONE;
                        if (x == -1)
                            cx = Color::BLUE;

                        if (y == 1)
                            cy = Color::RED;
                        if (y == 0)
                            cy = Color::NONE;
                        if (y == -1)
                            cy = Color::ORANGE;

                        if (z == 1)
                            cz = Color::WHITE;
                        if (z == 0)
                            cz = Color::NONE;
                        if (z == -1)
                            cz = Color::YELLOW;

                        Vector3D<int> coords = Vector3D(x, y, z);
                        Vector3D<Color> colors = Vector3D(cx, cy, cz);

                        pieces_.push_back(Piece{ coords, colors });
                    }
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const Cube& c)
        {
            for (Piece piece : c.pieces_)
                os << piece << '\n';

            return os;
        }

        static Cube from_stream(std::istream& is);

        std::vector<Piece>::iterator begin();
        std::vector<Piece>::iterator end();
        std::vector<Piece>::const_iterator begin() const;
        std::vector<Piece>::const_iterator end() const;

        Piece find_piece(Vector3D<int> coords) const;
        Piece find_piece(Vector3D<Color> colors) const;

        void do_move(Move move);
        void do_moves(std::vector<Move> moves);
        void undo_move(Move move);
        void undo_moves(std::vector<Move> moves);

    private:
        std::vector<Piece> pieces_;
    };
} // namespace rubik
