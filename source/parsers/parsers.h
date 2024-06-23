
#pragma once

//#define WITH_CHRONO
//#define WITH_PARSER 2

#include "impl_1.h"
#include "impl_2.h"

namespace parsers
{
    template <typename ...Args>
    void parse(Args&& ...args);

    namespace
    {
        typedef parsers::impl_1 impl_best_t;

#if !defined(WITH_PARSER)
        typedef impl_best_t impl_t;
#elif WITH_PARSER == 1
        typedef parsers::impl_1 impl_t;
#elif WITH_PARSER == 2
        typedef parsers::impl_2 impl_t;
#else // WITH_PARSER
        typedef impl_best_t impl_t;
#endif // WITH_PARSER
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename ...Args>
void parsers::parse(Args&& ...args)
{
#if WITH_CHRONO
    const auto start = std::chrono::high_resolution_clock::now();
#endif // WITH_CHRONO

    impl_t{}(std::forward<Args>(args)...);

#if WITH_CHRONO
    const auto end = std::chrono::high_resolution_clock::now();
    
    const std::chrono::duration<precision_t>& dt
    std::cout << "Completed in ";

    // Hours
    const int64_t dtH = std::chrono::duration_cast<std::chrono::hours>(dt).count();
    if (dtH > 0) std::cout << dtH << "h";

    // Minutes
    constexpr int64_t M_IN_S = 60;
    const int64_t dtM = std::chrono::duration_cast<std::chrono::minutes>(dt).count();
    const int64_t partM = dtM - dtH * M_IN_S;
    if (dtM > 0) std::cout << partM << "m";

    // Seconds + Microseconds (decimals)
    constexpr int64_t S_IN_M = 60; 
    const int64_t dtS = std::chrono::duration_cast<std::chrono::seconds>(dt).count();
    const int64_t partS = dtS - dtM * S_IN_M;

    constexpr int64_t S_IN_US = 1'000'000;
    const int64_t dtUs = std::chrono::duration_cast<std::chrono::microseconds>(dt).count();
    const int64_t partUs = dtUs - dtS * S_IN_US;
    
    constexpr precision_t usToS = static_cast<precision_t>(1.0 / static_cast<double>(S_IN_US));
    const precision_t realS = static_cast<precision_t>(partS) + static_cast<precision_t>(partUs) * usToS;
    std::cout << realS << "s";
#endif // WITH_CHRONO
}
