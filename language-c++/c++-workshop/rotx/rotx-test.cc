#include "rotx.hh"

int main(int argc, char** argv)
{
    if (argc != 3)
        return 1;

    // create the rotX class
    RotX rot(argv[1], atoi(argv[2]));

    // processing the input string
    rot.process();
}
