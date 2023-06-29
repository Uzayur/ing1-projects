// FIXME: You can include various files from the librubik library
#include <array>
#include <fstream>
#include <iostream>
#include <librubik/cube.hh>
#include <librubik/matrix3D.hh>
#include <librubik/move.hh>

int main()
{
    using namespace rubik;

    Cube cube;

    /**
    auto list = parse_moves("F' D' R2 x L' U B R F U2 F2 L2 L y2 F' B2 U2 D B'
z'");

    cube.do_moves(list);

    cube.undo_moves(list);
**/

    auto vect =
        parse_moves(" F' D' R2 x L' U B R F U2 F2 L2 L y2 F' B2 U2 D B' z'");

    cube.do_moves(vect);

    cube.undo_moves(vect);

    std::cout << cube << '\n';

    return 0;
}
