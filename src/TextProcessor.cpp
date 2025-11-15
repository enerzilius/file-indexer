#include "TextProcessor.h"

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <sstream>
#include <locale>
#include <codecvt>

std::vector<std::string> TextProcessor::processar(std::filesystem::path path) {
    std::string text = readTextFile(path);

    char delimiter = ' ';
	std::vector<std::string> processed = split(text, delimiter);
	lowerText(processed);
	for (auto word : processed) trim(word);
	clean(processed);

	return processed;
}

std::string TextProcessor::readTextFile(const std::filesystem::path& path) {
	if(!std::filesystem::exists(path)) {
		std::cout<<"\n  [!] Caminho não existe: "<<path.string()<<"\n";
		return "";
	}

	if(!std::filesystem::is_regular_file(path)) {
		std::cout<<"  [!] Arquivo imcompatível: "<<path.string()<<"\n";
		return "";
	}

    auto size = std::filesystem::file_size(path);
    std::string content(size, '\0');
    std::ifstream in(path);
    in.read(&content[0], size);

    return content;
}

std::vector<std::string> TextProcessor::split(std::string& text, const char& delimiter) {
	std::stringstream stream(text);
	std::vector<std::string> res;
	std::string segment;
	while(std::getline(stream, segment, delimiter))
	{
		res.push_back(segment);
	}
	return res;
}

void TextProcessor::lowerText(std::vector<std::string>& textVector) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    for (std::string& word : textVector) {
		std::wstring ws = conv.from_bytes(word);

		// Lowercase using towlower
		std::locale loc("C.UTF-8"); // or "pt_BR.UTF-8"
		for (wchar_t& wc : ws) {
			wc = std::tolower(wc, loc);
		}

		// Convert back wide string -> UTF-8
		word = conv.to_bytes(ws);
    }
}

void TextProcessor::clean(std::vector<std::string>& textVector) {
	std::filesystem::path path = "stopwords.txt";
	std::string rawStopWords = readTextFile(path);
	std::vector<std::string> stopWords = split(rawStopWords, ' ');
	for (auto word : stopWords) trim(word);

	std::unordered_set<std::string> stopsHash;
	for(auto word : stopWords) stopsHash.insert(word);
	
	auto it = textVector.begin();
	for (auto word : stopsHash) std::cout<<word<<"-";

	std::cout<<"\nmais| "<<stopsHash.count("mais")<<" \n";
	while (it != textVector.end()) {
		// std::cout<<*it<<"\n";
		bool check = *it == "\n" || *it == "";
		std::cout<<*it<<"| "<<stopsHash.count(*it)<<" \n";
		if (stopsHash.count(*it) > 0 || check) it = textVector.erase(it);
		else ++it;
	} 
}

void TextProcessor::trim(std::string& word) {
	word.erase(0,word.find_first_not_of(" \n\r\t"));
    word.erase(word.find_last_not_of(" \n\r\t")+1);
}