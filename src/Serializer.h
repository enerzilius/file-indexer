#pragma once

#include <unordered_map>
#include <filesystem>
#include "Index.h"

class Serializer {
public:
    void salvar(Index index, std::filesystem::path directory);
    Index carregar(std::filesystem::path path);
};