#pragma once

#include <vector>
#include <string>

class Index {
public:
    void processar(std::string texto, std::string nome);
    std::string* getArquivosPorPalavra(std::string palavra);
    std::string getNomeAqruivoPorId(std::string id);
};