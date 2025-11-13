#pragma once

#include <string>
#include "Index.h"

class Serializer {
public:
    void salvar(std::string index, std::string arquivo);
    Index carregar(std::string arquivo);
};