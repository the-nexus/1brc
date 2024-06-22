
#pragma once

#include <algorithm>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <string>
#include <string_view>
#include <utility>

namespace solution_a
{
    constexpr unsigned short maxStationCount = 10'000;

    struct station_data_t
    {
        station_data_t() = delete;
        station_data_t(const float value)
            : minValue(value)
            , maxValue(value)
            , sumValue(value)
            , sumCount(1)
            {}

        float minValue = std::numeric_limits<float>::max();
        float maxValue = std::numeric_limits<float>::min();
        float sumValue = 0.f;
        unsigned short sumCount = 0;
    };

    void process_file(const std::filesystem::path& filePath)
    {
        std::ifstream file {filePath};
        if (!file)
        {
            std::cerr << "Could not read file " << std::quoted(filePath.c_str()) << std::endl;
            return;
        }

        std::unordered_map<size_t, std::string> labelMap;
        labelMap.reserve(maxStationCount);

        std::unordered_map<size_t, station_data_t> dataMap;
        dataMap.reserve(maxStationCount);

        std::string line;
        while (std::getline(file, line))
        {
            const auto separatorIt = std::find_if(std::cbegin(line), std::cend(line), [](const char c) { return c == ';'; });

            std::string_view labelView = line;
            labelView.remove_suffix(std::distance(separatorIt, std::cend(line)));

            std::string_view valueView = line;
            valueView.remove_prefix(std::distance(std::cbegin(line), separatorIt) + 1);

            float value;
            std::from_chars(valueView.data(), valueView.data() + valueView.size(), value);

            const size_t labelHash = std::hash<std::string_view>{}(labelView);
            const auto [it, emplaced] = dataMap.try_emplace(labelHash, value);

            if (!emplaced)
            {
                station_data_t& data = it->second;
                data.minValue = std::min(data.minValue, value);
                data.maxValue = std::max(data.maxValue, value);
                data.sumValue += value;
                ++data.sumCount;
            }
            else
            {
                std::string label {labelView};
                labelMap.emplace(labelHash, std::move(label));
            }
        }

        file.close();

        bool isFirstEntry = true;
        const std::streamsize default_cout_precision = std::cout.precision();
        std::cout << std::fixed << std::setprecision(1) << "{";
        for (const auto& [labelHash, data] : dataMap)
        {
            std::cout << (isFirstEntry ? "" : ",");
            isFirstEntry = false;

            const float meanValue = data.sumValue / static_cast<float>(data.sumCount);
            const std::string& label = labelMap[labelHash];
            
            std::cout << std::quoted(label)
                << ":{ "
                << "\"min\":" << data.minValue
                << ",\"max\":" << data.maxValue
                << ",\"mean\":" << meanValue
                << "}";
        }
        std::cout << "}" << std::setprecision(default_cout_precision) << std::defaultfloat << std::endl;
    }
};
