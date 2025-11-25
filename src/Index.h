#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

class Index {
public:
    // O index tem um map <palavra, vetor de ids em que aparece>
    std::unordered_map<std::string, std::vector<int>> filesMap;
    // diretório
    std::filesystem::path directory;
    // métodos
    Index(std::filesystem::path dir);
    void adicionar(std::string word, int idArquivo);
    std::vector<int> getArquivosPorPalavra(std::string palavra);
    std::string getNomeArquivoPorId(int id);
    void printContent();
};