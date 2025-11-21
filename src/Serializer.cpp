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
    std::ofstream file;
    file.open(fileName, std::ios::binary);
    if(!file) {
        std::cout<<" [!] Erro ao construir arquivo "<<fileName<<"\n";
        return; 
    }

    std::string dirStr = index.directory.string();
    size_t dirSize = dirStr.size();
    file.write((char*)&dirSize, sizeof(dirSize));
    file.write(dirStr.data(), dirSize);

    size_t mapSize = index.filesMap.size();
    file.write((char*)&mapSize, sizeof(mapSize));

    for (auto& [word, vec] : index.filesMap) {
        size_t wordSize = word.size();
        file.write((char*)&wordSize, sizeof(wordSize));
        file.write(word.data(), wordSize);

        size_t vecSize = vec.size();
        file.write((char*)&vecSize, sizeof(vecSize));
        file.write((char*)vec.data(), vecSize * sizeof(int));
    }
    
    file.close();
}

Index Serializer::carregar(std::filesystem::path path) {
    Index index("");
    if(!std::filesystem::is_regular_file(path)) {
        std::cout<<"  [!] Há um problema com o arquivo: "<<path.string()<<"\n";
		return index;
	}
    
    std::ifstream file;
    file.open(path.string(), std::ios::binary);

    if(!file) {
        std::cout<<" [!] Erro ao ler o arquivo "<<path.string()<<"\n";
        return index;
    }

    size_t dirSize;
    file.read((char*)&dirSize, sizeof(dirSize));
    std::string dirStr(dirSize, '\0');
    file.read(dirStr.data(), dirSize);
    index.directory = dirStr;

    size_t mapSize;
    file.read((char*)&mapSize, sizeof(mapSize));

    for (size_t i = 0; i < mapSize; i++) {
        // Read word
        size_t wordSize;
        file.read((char*)&wordSize, sizeof(wordSize));
        std::string word(wordSize, '\0');
        file.read(word.data(), wordSize);

        // Read vector
        size_t vecSize;
        file.read((char*)&vecSize, sizeof(vecSize));
        std::vector<int> vec(vecSize);
        file.read((char*)vec.data(), vecSize * sizeof(int));

        index.filesMap[word] = std::move(vec);
    }

    return index;
}