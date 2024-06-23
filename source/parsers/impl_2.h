
#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace parsers
{
    struct impl_2
    {
        void operator()(const std::filesystem::path& filePath) const;
    };
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void parsers::impl_2::operator()(const std::filesystem::path& filePath) const
{
    //std::ifstream file {filePath, std::ios::binary};
    std::ifstream file {filePath, std::ios::binary};
    if (!file)
    {
        std::cerr << "Could not read file " << std::quoted(filePath.c_str()) << std::endl;
        return;
    }

    file.close();
}
