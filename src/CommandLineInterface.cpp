#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "CommandLineInterface.h"
#include "TextProcessor.h"
#include "Indexer.h"
#include "Index.h"
#include "Serializer.h"
#include "QueryProcessor.h"

void CLI::start() {
    std::cout<< "\n\n    INDEXADOR DE ARQUIVOS" << "\n\n";
    std::cout<<" Comandos:\n $ indice construir <diretorio> # Constroi o índice inverso do diretório.\n"; 
    std::cout<<" $ indice buscar <termo_de_busca> # Pode usar mais de um termo de busca.\n";
    std::cout<<" $ indice limpar # Exclui o arquivo index.dat\n\n";

    availableCommands.insert("construir");
    availableCommands.insert("buscar");
    availableCommands.insert("limpar");

    std::string input;

    while(true) {
        std::cout<<" >> ";
        std::getline(std::cin, input);

        const char delimiter = ' ';
        std::vector<std::string> splitString = split(input, delimiter);

         processInput(splitString);
        
        std::cout<<"\n";
    }
}

void CLI::processInput(std::vector<std::string> commands) {
    if(commands.size() < 2 || availableCommands.count(commands[1]) <= 0) {
        std::cout<< "\n [!] Comando inválido...\n";
        std::cout<<"     Use os comandos listados ao inicializar a aplicação.\n";
        return;
    }

    if(commands.size() < 3 && commands[1] != "limpar") {
        std::cout<< "\n [!] Diretório ou termo de busca não específicados...\n";
        std::cout<<"     Use: `indice construir <caminho_do_diretorio>` ou `indice buscar <termo_de_busca>`\n";
        return;
    }

    if(commands[1] == "construir") {
        std::filesystem::path directory = commands[2];
        std::cout<<"\n\n [construir]: "<<directory.string();
        
        Indexer indexer;
        Index index = indexer.construir(directory);

        if(index.filesMap.empty()) return;
        Serializer serializer;
        serializer.salvar(index, directory);       
    }
    if(commands[1] == "buscar") {
        std::cout<<"\n [buscar]\n\n";
        QueryProcessor queryProcessor;
        queryProcessor.buscar(commands);
    }
    if(commands[1] == "limpar") {
        std::cout<<"\n [limpar]\n";
        std::string fileName = "index.dat";
        if (std::filesystem::exists(fileName)) {
            std::filesystem::remove(fileName);
        } 
    }
}