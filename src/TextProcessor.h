#pragma once

#include <vector>
#include <string>
#include <filesystem>

class TextProcessor {
public:
    std::vector<std::string> processar(std::string texto); 
    std::string readTextFile(const std::filesystem::path& path);
};