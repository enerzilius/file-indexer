#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class Index {
public:
    void adicionar(std::string word, int id_arquivo);
    std::vector<std::string> getArquivosPorPalavra(std::string palavra);
    std::string getNomeAqruivoPorId(std::string id);
    std::unordered_map<std::string, std::vector<int>> filesMap;
};