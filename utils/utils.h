#include <string>
#include <vector>
#include <filesystem>

std::vector<std::string> split(std::string& text, const std::string& delimiter);
bool directoryExists(std::filesystem::path path);