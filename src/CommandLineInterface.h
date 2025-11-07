#pragma once

#include "Index.h"
#include "QueryProcessor.h"
#include "Serializer.h"

class CLI {
public:
    void start();
    void processInput(std::string* commands);
};
