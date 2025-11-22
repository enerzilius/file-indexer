#pragma once

#include <vector>
#include <string>
#include <unordered_set>

class CLI {
public:
    void start();
    void processInput(std::vector<std::string> commands);    
    std::unordered_set<std::string> availableCommands;
};
