#include <iostream>
#include "CommandLineInterface.h"

void CLI::start() {
    std::cout << "Iniciando indexador..." << "\n";

    std::string input;

    while(true) {
        std::cout<<" >> ";
        std::getline(std::cin, input);
        std::cout<<"\'"<<input<<"\'";
        std::cout<<"\n";
    }
}