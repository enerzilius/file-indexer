#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include "Index.h"

class Indexer {
public:
    Index construir(std::filesystem::path diretorio);
};