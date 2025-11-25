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

    // Cria um map com os comandos disponíveis para checar mais facilmente a validade dos comandos
    availableCommands.insert("construir");
    availableCommands.insert("buscar");
    availableCommands.insert("limpar");

    std::string input;

    // Entra em um loop que só quebra após o ctrl+c onde o programa espera para ler o input
    while(true) {
        std::cout<<" >> ";
        std::getline(std::cin, input);

        const char delimiter = ' ';
        std::vector<std::string> splitString = split(input, delimiter);

        // Processa o vetor com os comandos 
        processInput(splitString);
        
        std::cout<<"\n";
    }
}

void CLI::processInput(std::vector<std::string> commands) {
    //  Não é um comando válido se tiver só uma palavra ou não estiver dentro da lista de comandos
    if(commands.size() < 2 || availableCommands.count(commands[1]) <= 0) {
        std::cout<< "\n [!] Comando inválido...\n";
        std::cout<<"     Use os comandos listados ao inicializar a aplicação.\n";
        return;
    }

    // Só o limpar não precisa de outros termos
    if(commands.size() < 3 && commands[1] != "limpar") {
        std::cout<< "\n [!] Diretório ou termo de busca não específicados...\n";
        std::cout<<"     Use: `indice construir <caminho_do_diretorio>` ou `indice buscar <termo_de_busca>`\n";
        return;
    }

    if(commands[1] == "construir") {
        // Se o comando for "construir", chama o indexer que lê um diretório e cria um Index e o Serializer para criar o arquivo index.dat
        std::filesystem::path directory = commands[2];
        std::cout<<"\n\n [construir]: "<<directory.string();
        
        Indexer indexer;
        Index index = indexer.construir(directory);

        if(index.filesMap.empty()) return;
        Serializer serializer;
        serializer.salvar(index, directory);       
    }
    if(commands[1] == "buscar") {
        // Query processor é responsável pela busca
        std::cout<<"\n [buscar]\n\n";
        QueryProcessor queryProcessor;
        queryProcessor.buscar(commands);
    }
    if(commands[1] == "limpar") {
        std::cout<<"\n [limpar]\n";
        // Só exclui o index.dat por conveniência
        std::string fileName = "index.dat";
        if (std::filesystem::exists(fileName)) {
            std::filesystem::remove(fileName);
        } 
    }
}