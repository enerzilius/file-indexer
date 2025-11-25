#include "Serializer.h"
#include "Index.h"
#include <iostream>
#include <fstream>

// não achei legal esse aqui não professor LKKKKKK
void Serializer::salvar(Index index, std::filesystem::path directory) {
    if(!std::filesystem::exists(directory)) {
        std::cout<<"\n  [!] Diretório não existe: "<<directory.string()<<"\n";
        return;
	}
    
    // Remove o index.dat se já tiver um salvo 
    std::string fileName = "index.dat";
    if (std::filesystem::exists(fileName)) {
        std::filesystem::remove(fileName);
    }
    std::cout<<" SERIALIZER - Salvando arquivo "<<fileName<<"\n";
    std::ofstream file;
    file.open(fileName, std::ios::binary);
    if(!file) {
        std::cout<<" [!] Erro ao construir arquivo "<<fileName<<"\n";
        return; 
    }

    // Aqui ele vai escrever primeiro o tamanho do diretório e depois o real conteúdo da string
    std::string dirStr = index.directory.string();
    size_t dirSize = dirStr.size();
    file.write((char*)&dirSize, sizeof(dirSize));
    file.write(dirStr.data(), dirSize);

    // Também escreve o tamanho antes de escrever o conteúdo da tabela hash, esse é o padrão com tudo salvo aqui
    size_t mapSize = index.filesMap.size();
    file.write((char*)&mapSize, sizeof(mapSize));

    // Mesmo padrão: tamanho da palavra, palavra, tamanho do vetor, conteudo do vetor de ids (pra todos os elementos da tabela)
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
    std::cout<<" SERIALIZER - lendo arquivo: "<<path<<"\n";
    Index index("");
    if(!std::filesystem::is_regular_file(path)) {
        std::cout<<"  [!] Há um problema com o arquivo: "<<path.string()<<"\n";
		return index;
	}
    
    // abre o arquivo
    std::ifstream file;
    file.open(path.string(), std::ios::binary);

    if(!file) {
        std::cout<<" [!] Erro ao ler o arquivo "<<path.string()<<"\n";
        return index;
    }

    // Lê o tamanho da string diretório e usa essa informação para ler corretamente a string no arquivo 
    size_t dirSize;
    file.read((char*)&dirSize, sizeof(dirSize));
    std::string dirStr(dirSize, '\0');
    file.read(dirStr.data(), dirSize);
    index.directory = dirStr;

    // Aqui vai ser a mesma coisa, ler o tamanho e depois usar isso pra ler e salvar as informações na variável index
    size_t mapSize;
    file.read((char*)&mapSize, sizeof(mapSize));

    for (size_t i = 0; i < mapSize; i++) {
        size_t wordSize;
        file.read((char*)&wordSize, sizeof(wordSize));
        std::string word(wordSize, '\0');
        file.read(word.data(), wordSize);

        size_t vecSize;
        file.read((char*)&vecSize, sizeof(vecSize));
        std::vector<int> vec(vecSize);
        file.read((char*)vec.data(), vecSize * sizeof(int));

        // Usa um move para transferir os dados do vetor sem usar cópias !!
        index.filesMap[word] = std::move(vec);
    }

    return index;
}