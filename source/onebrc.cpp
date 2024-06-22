
#define WITH_CHRONO !defined(NO_CHRONO) && NO_CHRONO == 0

#include <filesystem>
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

    const std::filesystem::path filePath {  };
    //auto fileProcessor = [&filePath]() { solution_a::process_file(filePath); };

#ifdef NO_CHRONO

    solution_a::process_file(argv[1]);

#else // NO_CHRONO

    const auto dt = chrono_utils::measure_execution(&solution_a::process_file, argv[1]);
    std::cout << "Completed in ";
    chrono_utils::display(dt);
    std::cout << std::endl;

#endif // NO_CHRONO
    return 0;
}
