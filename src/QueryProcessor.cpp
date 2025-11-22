#include "QueryProcessor.h"
#include "Index.h"
#include "Serializer.h"
#include <vector>
#include <filesystem>
#include <iostream>
#include <unordered_set>

void QueryProcessor::buscar(std::vector<std::string> consulta) {
    std::string path = "index.dat";
    if(!std::filesystem::is_regular_file(path)) {
        std::cout<<" [!] Arquivo `index.dat` não encontrado! Execute o comando `indice construir <diretorio>` primeiro.\n";
        return;
    }
    
    Serializer serializer;
    Index index = serializer.carregar(path);
    std::cout<<" [*] Se você adicionou, removeu ou alterou algum arquivo do diretório: "<<index.directory<<" refaça o build para evitar erros. \n";

    std::unordered_set<int> idsMap;
    std::vector<int> intersection = index.filesMap.find(consulta[2])->second;
    for (int id : intersection) idsMap.insert(id);
    for(int i = 3; i < consulta.size(); i++) {
        intersection.clear();
        std::vector<int> idsVector = index.filesMap.find(consulta[i])->second;
        for(int id : idsVector) if(idsMap.count(id) > 0) intersection.push_back(id);
        idsMap.clear(); 
        for(int id : intersection) idsMap.insert(id);
    }

    if(idsMap.empty()) {
        std::cout<<" [*] Nenhum arquivo apresenta os termos desejados.\n\n";
        return;
    }

    std::cout<<"\n Termo(s) encontrado(s) em: \n";
    for(int id :idsMap) {
        std::cout<<"  "<<index.getNomeArquivoPorId(id)<<"\n";
    }
    std::cout<<"\n";
}