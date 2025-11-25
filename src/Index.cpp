#include "Index.h"
// #include "TextProcessor.h"
#include <vector>
#include <unordered_map>
#include <iostream>

Index::Index(std::filesystem::path dir) {
    directory = dir;
}

void Index::adicionar(std::string word, int idArquivo) {
    // Se não tiver a palavra no map, cria uma 'linha' nova na tabela com a palavra e um vetor só com o id do arquivo
    auto it = filesMap.find(word);
    if (it == filesMap.end()) {
        filesMap.insert({word, {idArquivo}});
        return;
    }
    // Se o id já estiver no vetor de ids, não é adiconado de novo (seria mais fácil só usar um set mas pareceu estranho então não fiz KKKKK)
    for(auto e : it->second) if(e == idArquivo) return;

    it->second.push_back(idArquivo); 
}

std::vector<int> Index::getArquivosPorPalavra(std::string palavra) {
    // Retorna o vetor de ids caso encontre a palavra desejada
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
    if(!std::filesystem::exists(directory)) {
		std::cout<<"\n  [!] Diretório não existe: "<<directory.string()<<"\n";
		return "";
	}

    // Se o diretório existir, itera pelo diretório e retorna o caminho do arquivo que o i == id
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
    // imprime todo o conteúdo do map (por conveniência nos testes)
    std::cout<<"\n Diretório: "<<directory<<"\n";
    for(auto pair : filesMap) {
        std::cout<<"Chave: "<<pair.first<<" - ";
        for(auto id : pair.second) std::cout<<id<<" ";
        std::cout<<"\n";
    }
}