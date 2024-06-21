
#define WITH_CHRONO !defined(NO_CHRONO)

#include <filesystem>
#include <iostream>

#include "solution_a.h"

#if WITH_CHRONO
#include <chrono>
#endif

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "No argument specified, expected path to input file." << std::endl;
        return -1;
    }

#if WITH_CHRONO

    const auto start = std::chrono::high_resolution_clock::now();
    solution_a::display(argv[1]);
    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> deltaTime {end - start};
    std::cout << "Completed in ";

    const int64_t deltaTimeM = std::chrono::duration_cast<std::chrono::minutes>(deltaTime).count();
    const int64_t deltaTimeS = std::chrono::duration_cast<std::chrono::seconds>(deltaTime).count();
    const int64_t deltaTimeNs = std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime).count();

    const int64_t partS = deltaTimeS - deltaTimeM * 60;
    const int64_t partNs = deltaTimeNs - deltaTimeS * 1000;

    const double seconds = static_cast<double>(partS) + static_cast<double>(partNs) / 1000.0;

    if (deltaTimeM > 0)
    {
        std::cout << deltaTimeM << "m";
    }
    
    std::cout << seconds << "s" << std::endl;

#else // WITH_CHRONO

    solution_a::display(argv[1]);
    
#endif // WITH_CHRONO

    return 0;
}
