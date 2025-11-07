#include "utils.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

std::vector<std::string> split(std::string& text, const std::string& delimiter) {
	std::vector<std::string> res;
	int i = 0;
	while ((i = text.find(delimiter)) != std::string::npos) {
		std::string word = text.substr(0, i);
		res.push_back(word);
		text.erase(0, i + delimiter.length());
	}
	res.push_back(text);
	return res;
}

std::string readTextFile(const fs::path& path) {
	if(!fs::exists(path)) {
		std::cout<<"  [!] Caminho não existe: "<<path.string()<<"\n";
		return;
	}

	if(!fs::is_regular_file(path)) {
		std::cout<<"  [!] Arquivo imcompatível: "<<path.string()<<"\n";
		return;
	}


}