
#include <iostream>

#include "chrono_utils.h"
#include "solution_a.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "No argument specified, expected path to input file." << std::endl;
        return -1;
    }

#ifdef WITH_CHRONO

    const auto dt = chrono_utils::measure_execution(&solution_a::process_file, argv[1]);
    std::cout << "Completed in ";
    chrono_utils::display(dt);
    std::cout << std::endl;

#else // WITH_CHRONO
    
    solution_a::process_file(argv[1]);

#endif // WITH_CHRONO
    return 0;
}
