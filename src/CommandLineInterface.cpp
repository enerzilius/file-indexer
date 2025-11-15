#include <iostream>
#include <string>
#include <unordered_map>
#include "CommandLineInterface.h"
#include "TextProcessor.h"

void CLI::start() {
    std::cout << "Iniciando indexador (por Eber Louback)..." << "\n";

    std::string input;

    TextProcessor textProcessor;

    while(true) {
        auto vec = textProcessor.processar("texts/teste.txt");
        std::cout<<"---------------------\n";
        for (auto el : vec)
        {
            std::cout<<el<<"\n";
        }
        
        
        std::cout<<" >> ";
        std::getline(std::cin, input);
        std::cout<<"Executando: \'"<<input<<"\'...\n";


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
        std::cout<<"\n [construir]: "<<commands[2];
    }
    if(commands[1] == "buscar") {
        std::cout<<"\n [buscar]: "<<commands[2];
    }
}