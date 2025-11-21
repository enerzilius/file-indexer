#include <iostream>
#include <string>
#include <unordered_map>
#include "CommandLineInterface.h"
#include "TextProcessor.h"
#include "Indexer.h"
#include "Index.h"
#include "Serializer.h"

void CLI::start() {
    std::cout << "Iniciando indexador..." << "\n";

    std::string input;

    TextProcessor textProcessor;

    while(true) {
        std::cout<<" >> ";
        std::getline(std::cin, input);

        const char delimiter = ' ';
        std::vector<std::string> splitString = textProcessor.split(input, delimiter);

         processInput(splitString);
        
        std::cout<<"\n";
    }
}

void CLI::processInput(std::vector<std::string> commands) {
    if(commands.size() < 2 || commands[0] != "indice" || (commands[1] != "construir" && commands[1] != "buscar")) {
        std::cout<< "\n [!] Comando inválido...\n";
        std::cout<<"     Use os seguintes comandos: `indice construir <caminho_do_diretorio>` ou `indice buscar <termo_de_busca>`\n";
        return;
    }

    if(commands.size() < 3) {
        std::cout<< "\n [!] Diretório ou termo de busca não específicados...\n";
        std::cout<<"     Use: `indice construir <caminho_do_diretorio>` ou `indice buscar <termo_de_busca>`\n";
        return;
    }

    if(commands[1] == "construir") {
        std::cout<<"\n\n [construir]: "<<commands[2];
        Indexer indexer;
        Index index = indexer.construir(commands[2]);

    }
    if(commands[1] == "buscar") {
        std::cout<<"\n [buscar]: "<<commands[2];
    }
}