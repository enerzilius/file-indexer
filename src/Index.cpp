#include "Index.h"
// #include "TextProcessor.h"
#include <vector>
#include <unordered_map>
#include <iostream>

Index::Index(std::filesystem::path dir) {
    directory = dir;
}

void Index::adicionar(std::string word, int idArquivo) {
    auto it = filesMap.find(word);
    if (it == filesMap.end()) {
        filesMap.insert({word, {idArquivo}});
        return;
    }
    for(auto e : it->second) if(e == idArquivo) return;

    it->second.push_back(idArquivo); 
}

std::vector<int> Index::getArquivosPorPalavra(std::string palavra) {
    auto it = filesMap.find(palavra);
    std::vector<int> filesIds = {-1};
    if (it == filesMap.end()) {
        std::cout<<" [!] Termo procurado não aparece em nenhum arquivo.\n";
        return filesIds;
    }

    filesIds = it->second;
    return filesIds;
}

std::string Index::getNomeArquivoPorId(int id) {
    std::cout<<" [*] Se você adicionou, removeu ou alterou algum arquivo deste diretório, refaça o build para evitar erros. \n";
    if(!std::filesystem::exists(directory)) {
		std::cout<<"\n  [!] Diretório não existe: "<<directory.string()<<"\n";
		return "";
	}

    // TextProcessor tp;
    int i = 1;
    for(auto& entry : std::filesystem::directory_iterator(directory)) {
        if(!std::filesystem::is_regular_file(entry.path())) continue;
        if(i == id) return entry.path().string();
        i++;
    }
    std::cout<<" [!] Arquivo não encontrado, tente refazer o índice deste diretório.";
    return "";
}

void Index::printContent() {
    std::cout<<"\n Diretório: "<<directory<<"\n";
    for(auto pair : filesMap) {
        std::cout<<"Chave: "<<pair.first<<" - ";
        for(auto id : pair.second) std::cout<<id<<" ";
        std::cout<<"\n";
    }
}