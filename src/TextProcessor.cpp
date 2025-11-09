#include "TextProcessor.h"
#include "../utils/utils.h"

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
std::vector<std::string> TextProcessor::processar(std::string texto) {
    std::vector<std::string> processed;

    std::string delimiter = " ";
    processed = split(texto,  delimiter);

    std::vector<std::string> stopWords;
    

    return processed;
}

std::string TextProcessor::readTextFile(const std::filesystem::path& path) {
	if(!std::filesystem::exists(path)) {
		std::cout<<"  [!] Caminho não existe: "<<path.string()<<"\n";
		return;
	}

	if(!std::filesystem::is_regular_file(path)) {
		std::cout<<"  [!] Arquivo imcompatível: "<<path.string()<<"\n";
		return;
	}

    std::ifstream file(path.string());

}