#include "Serializer.h"
#include "Index.h"
#include <iostream>
#include <fstream>

void Serializer::salvar(Index index, std::filesystem::path directory) {
    if(!std::filesystem::exists(directory)) {
		std::cout<<"\n  [!] Diretório não existe: "<<directory.string()<<"\n";
        return;
	}

    std::string fileName = directory.string() + "/index.dat";
    std::cout<<fileName<<"\n";
    std::fstream file;
    file.open(fileName);
    if(!file) {
        std::cout<<" [!] Erro ao construir arquivo "<<fileName<<"\n";
        return;
    }

    file.write(reinterpret_cast<char*>(&index), sizeof(index));
    file.close();
}