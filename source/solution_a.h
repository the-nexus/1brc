
#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace solution_a
{
    void display(const std::filesystem::path& filePath)
    {
        std::ifstream file(filePath);
        if (!file)
        {
            std::cerr << "Could not read file " << std::quoted(filePath.c_str()) << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << "\n";
        }

        std::cout << std::endl;
        file.close();
    }
};
