#include "QueryProcessor.h"
#include "Index.h"
#include "Serializer.h"
#include <vector>
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

void QueryProcessor::buscar(std::vector<std::string> consulta) {
    // Sempre vai buscar no root/index.dat
    std::string path = "index.dat";
    if(!std::filesystem::is_regular_file(path)) {
        std::cout<<" [!] Arquivo `index.dat` não encontrado! Execute o comando `indice construir <diretorio>` primeiro.\n";
        return;
    }
    
    // aviso
    Serializer serializer;
    // Carrega o index.dat
    Index index = serializer.carregar(path);
    std::cout<<" [*] Se você adicionou, removeu, renomeou ou alterou algum arquivo do diretório: "<<index.directory<<" refaça o build para evitar erros. \n";


    // Aqui vai iterar pelos termos de busca (i = 2 pra frente no vetor do comando)
    std::unordered_set<int> idsMap;
    
    bool first = true;
    for(int i = 2; i < consulta.size(); i++) {
        // Ele tenta encontrar a palavra no map do index, se não achar já pula
        auto find = index.filesMap.find(consulta[i]);
        if(find == index.filesMap.end()) {
            idsMap.clear();
            break;
        }

        // Se o termo existir, pega o vetor de ids dele
        std::vector<int> idsVector = find->second;

        // Isso aqui é pra ele não passar direto na primeira iteração por não ter nada no set
        if (first) {
            for (int id : idsVector) idsMap.insert(id);
            first = false;
            continue;
        }

        // Pega a interseccão entre os ids no set e os desta palavra
        std::vector<int> intersection = {};
        for(int id : idsVector) if(idsMap.count(id) > 0) intersection.push_back(id);  

        // Limpa o set para remover direto todos que não vão estar no intersection e coloca os elementos dele no set
        idsMap.clear();
        for (int id : intersection) idsMap.insert(id);

        if (idsMap.empty()) break; 
    }

    if(idsMap.empty()) {
        std::cout<<" [*] Nenhum arquivo apresenta os termos desejados.\n\n";
        return;
    }

    // Imprime os nomes dos arquivos
    std::cout<<"\n Termo(s) encontrado(s) em: \n";
    for(int id :idsMap) {
        std::cout<<"  "<<index.getNomeArquivoPorId(id)<<"\n";
    }
    std::cout<<"\n";
}