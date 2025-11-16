#include "Index.h"
#include <vector>

void Index::adicionar(std::string word, int id_arquivo) {
    auto it = map.find(word);
    if (it == map.end()) {
        map.insert({word, {id_arquivo}});
        return;
    }
    it->second.push_back(id_arquivo); 
}