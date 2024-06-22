
#include <iostream>

#include "parsers/parser_a.h"
#include "utils/chrono_utils.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "No argument specified, expected path to input file." << std::endl;
        return -1;
    }

#ifdef WITH_CHRONO

    const auto dt = chrono_utils::measure_execution(&parser_a::parse, argv[1]);
    std::cout << "Completed in ";
    chrono_utils::display(dt);
    std::cout << std::endl;

#else // WITH_CHRONO
    
    parser_a::parse(argv[1]);

#endif // WITH_CHRONO
    return 0;
}
