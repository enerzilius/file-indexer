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

    for(auto& entry : std::filesystem::directory_iterator(diretorio)) {
        if(!std::filesystem::is_regular_file(entry.path())) continue;
        tp.processar(entry.path());
    }

    return index;
}
