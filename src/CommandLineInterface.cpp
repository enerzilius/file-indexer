#include <iostream>
#include <string>
#include "CommandLineInterface.h"
#include "../utils/utils.h"

void CLI::start() {
    std::cout << "Iniciando indexador..." << "\n";

    std::string input;

    while(true) {
        std::cout<<" >> ";
        std::getline(std::cin, input);
        std::cout<<"Executando: \'"<<input<<"\'...";

        std::string delimiter = " ";
        std::string* splitString = split(input, delimiter);

        
        std::cout<<"\n";
    }
}