
#pragma once

#include <algorithm>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <string>
#include <string_view>
#include <utility>

#include "../models/station.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace parsers
{
    struct impl_1
    {
        void operator()(const std::filesystem::path& filePath) const;
    };
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void parsers::impl_1::operator()(const std::filesystem::path& filePath) const
{
    std::ifstream file {filePath};
    if (!file)
    {
        std::cerr << "Could not read file " << std::quoted(filePath.c_str()) << std::endl;
        return;
    }

    std::unordered_map<size_t, std::string> labelMap;
    labelMap.reserve(models::station::maxInstanceCount);

    std::unordered_map<size_t, models::station> stationMap;
    stationMap.reserve(models::station::maxInstanceCount);

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
        const auto [it, emplaced] = stationMap.try_emplace(labelHash, value);

        if (!emplaced)
        {
            models::station& model = it->second;
            model.minValue = std::min(model.minValue, value);
            model.maxValue = std::max(model.maxValue, value);
            model.sumValue += value;
            ++model.instanceCount;
        }
        else
        {
            std::string label {labelView};
            labelMap.emplace(labelHash, std::move(label));
        }
    }

    file.close();

    const std::streamsize oldPrecision = std::cout.precision();
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "{";
    
    bool isFirstEntry = true;
    for (const auto& [labelHash, model] : stationMap)
    {
        std::cout << (isFirstEntry ? "" : ",");
        isFirstEntry = false;

        const std::string& label = labelMap[labelHash];
        std::cout << std::quoted(label) << ":" << model;
    }

    std::cout << "}";
    std::cout << std::setprecision(oldPrecision) << std::defaultfloat << std::endl;
}
