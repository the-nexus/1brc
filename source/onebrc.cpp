
#include <iostream>

#include "parsers/parsers.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "No argument specified, expected path to input file." << std::endl;
        return -1;
    }

    parsers::parse(argv[1]);
}
