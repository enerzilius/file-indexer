#include "Index.h"
#include <vector>
#include <unordered_map>

void Index::adicionar(std::string word, int id_arquivo) {
    auto it = filesMap.find(word);
    if (it == filesMap.end()) {
        filesMap.insert({word, {id_arquivo}});
        return;
    }
    for(auto e : it->second) if(e == id_arquivo) return;
    
    it->second.push_back(id_arquivo); 
}