#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <unordered_set>

class TextProcessor {
public:
    TextProcessor();
    std::unordered_set<std::string> processar(std::filesystem::path path); 
private:
    std::unordered_set<std::string> stopWordsSet;
    std::string readTextFile(const std::filesystem::path& path);
    void lowerText(std::unordered_set<std::string>& text);
    void trimText(std::unordered_set<std::string>& text);
    void clean(std::unordered_set<std::string>& text);
    std::string trim(std::string word);
};

std::vector<std::string> split(std::string& text, const char& delimiter);