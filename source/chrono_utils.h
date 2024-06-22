
#pragma once

#include <chrono>
#include <iostream>
#include <utility>

namespace chrono_utils
{
    typedef double precision_t;

    template <typename Func>
    std::chrono::duration<precision_t> measure_execution(Func&& function)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        function();
        const auto end = std::chrono::high_resolution_clock::now();
        return {end - start};
    }

    template <typename Func, typename ...Args>
    std::chrono::duration<precision_t> measure_execution(Func&& function, Args&& ...args)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        function(std::forward<Args>(args)...);
        const auto end = std::chrono::high_resolution_clock::now();
        return {end - start};
    }

    void display(const std::chrono::duration<precision_t>& dt)
    {
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
    }
}
