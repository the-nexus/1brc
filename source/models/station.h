
#pragma once

#include <limits>

namespace models
{
    struct station
    {
        static constexpr unsigned int maxInstanceCount = 10'000;

        unsigned int instanceCount = 0;
        float minValue = std::numeric_limits<float>::max();
        float maxValue = std::numeric_limits<float>::min();
        float sumValue = 0.f;

        station() = delete;
        station(const float value)
            : instanceCount(1)
            , minValue(value)
            , maxValue(value)
            , sumValue(value)
            {}
            
        inline float get_mean() const { return sumValue / static_cast<float>(instanceCount); }
    };
}
