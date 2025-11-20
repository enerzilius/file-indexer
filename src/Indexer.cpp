#include "Indexer.h"

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include "Index.h"
#include "TextProcessor.h"

Index Indexer::construir(std::filesystem::path diretorio) {
    Index index;
    if(!std::filesystem::exists(diretorio)) {
		std::cout<<"\n  [!] Caminho não existe: "<<diretorio.string()<<"\n";
		return index;
	}

    TextProcessor tp;
    int i = 1;
    for(auto& entry : std::filesystem::directory_iterator(diretorio)) {
        if(!std::filesystem::is_regular_file(entry.path())) continue;
        auto words = tp.processar(entry.path());
        for(std::string word : words) index.adicionar(word, i);
        i++;
    }

    for (auto e : index.filesMap)
    {
        std::cout<<e.first<<" - ";
        for (auto f : e.second)
        {
            std::cout<<f<<" ";
        }
        std::cout<<"\n";
    }
    



    return index;
}
