#pragma once

#include <vector>
#include <string>
#include <filesystem>

class TextProcessor {
public:
    std::vector<std::string> processar(std::filesystem::path path); 
    std::vector<std::string> split(std::string& text, const char& delimiter);
private:
    std::string readTextFile(const std::filesystem::path& path);
    void lowerText(std::vector<std::string>& textVector);
    void clean(std::vector<std::string>& textVector);
    void trim(std::string& word);
};