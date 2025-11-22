#include "QueryProcessor.h"
#include "Index.h"
#include "Serializer.h"
#include <vector>
#include <filesystem>
#include <iostream>
#include <unordered_map>

void QueryProcessor::buscar(std::vector<std::string> consulta) {
    std::string path = "index.dat";
    if(!std::filesystem::is_regular_file(path)) {
        std::cout<<" [!] Arquivo `index.dat` não encontrado! Execute o comando `indice construir <diretorio>` primeiro.\n";
        return;
    }
    
    Serializer serializer;
    Index index = serializer.carregar(path);
    std::cout<<" [*] Se você adicionou, removeu ou alterou algum arquivo do diretório:"<<index.directory<<", refaça o build para evitar erros. \n";

    std::vector<int> ids = index.filesMap.find(consulta[2])->second;
    std::cout<<"\n Termo encontrado em: \n";
    for (int id : ids) {
        std::cout<<"  "<<index.getNomeArquivoPorId(id)<<"\n";
    }
}