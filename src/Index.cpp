#include "Index.h"
#include <vector>

void Index::adicionar(std::string word, int id_arquivo) {
    auto it = ids.find(word);
    if (it == ids.end()) {
        ids.insert({word, {id_arquivo}});
        return;
    }
    it->second.push_back(id_arquivo); 
}