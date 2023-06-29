#include <iostream>

#include "replace.hh"

int main(int argc, char** argv)
{
    if (argc < 5)
    {
        std::cerr << "Usage: INPUT_FILE OUTPUT_FILE SRC_TOKEN DST_TOKEN\n";
        return 1;
    }

    replace(argv[1], argv[2], argv[3], argv[4]);

    return 0;
}
