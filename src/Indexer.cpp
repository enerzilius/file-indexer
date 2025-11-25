#include "Indexer.h"

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include "Index.h"
#include "TextProcessor.h"

Index Indexer::construir(std::filesystem::path diretorio) {
    Index index(diretorio);
    if(!std::filesystem::exists(diretorio)) {
		std::cout<<"\n  [!] Caminho não existe: "<<diretorio.string()<<"\n";
		return index;
	}

    // Se o diretório existir, adiciona as palavras dos arquivos junto do id (a posição atual no diretório) no index
    // Funciona perfeitamente bem se não houver nenhuma alteração nos arquivos do diretório, se houver precisa de um rebuild
    TextProcessor tp = TextProcessor();
    int i = 1;
    for(auto& entry : std::filesystem::directory_iterator(diretorio)) {
        if(!std::filesystem::is_regular_file(entry.path())) continue;
        auto words = tp.processar(entry.path());
        for(std::string word : words) index.adicionar(word, i);
        i++;
    }

    return index;
}
