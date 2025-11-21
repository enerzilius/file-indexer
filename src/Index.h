#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

class Index {
public:
    std::unordered_map<std::string, std::vector<int>> filesMap;
    std::filesystem::path directory;
    Index(std::filesystem::path dir);
    void adicionar(std::string word, int id_arquivo);
    std::vector<int> getArquivosPorPalavra(std::string palavra);
    std::string getNomeArquivoPorId(int id);
};