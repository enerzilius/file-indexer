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

TextProcessor::TextProcessor() {
	std::filesystem::path path = "stopwords.txt";
	std::string rawStopWords = readTextFile(path);
	std::vector<std::string> stopWords = split(rawStopWords, ' ');
	for (auto& word : stopWords) trim(word);

	for(auto& word : stopWords) stopWordsSet.insert(word);
}

std::unordered_set<std::string> TextProcessor::processar(std::filesystem::path path) {
	std::cout<<"\n Processando: "<<path<<"\n";
    std::string text = readTextFile(path);

    char delimiter = ' ';
	std::vector<std::string> wordVector = split(text, delimiter);
	std::unordered_set<std::string> wordsSet;
	for(auto& word : wordVector) wordsSet.insert(word);
	lowerText(wordsSet);
	trimText(wordsSet);
	clean(wordsSet);

	return wordsSet;
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

std::vector<std::string> split(std::string& text, const char& delimiter) {
	std::stringstream stream(text);
	std::vector<std::string> res;
	std::string segment;
	while(std::getline(stream, segment, delimiter))
	{
		res.push_back(segment);
	}
	return res;
}

void TextProcessor::lowerText(std::unordered_set<std::string>& text) {
    std::unordered_set<std::string> lowered;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

    std::locale loc("C.UTF-8");

    for (const auto& word : text) {
        std::wstring ws = conv.from_bytes(word);
        for (wchar_t& wc : ws) {
            wc = std::tolower(wc, loc);
        }
        lowered.insert(conv.to_bytes(ws));
    }

    text.swap(lowered);
}
void TextProcessor::trimText(std::unordered_set<std::string>& text) {
    std::unordered_set<std::string> trimmed;

    for (const auto& word : text) {
		trimmed.insert(trim(word));
    }

    text.swap(trimmed);
}

void TextProcessor::clean(std::unordered_set<std::string>& text) {
	auto it = text.begin();

	while (it != text.end()) {
		bool check = *it == "\n" || *it == "";
		if (stopWordsSet.count(*it) > 0 || check) it = text.erase(it);
		else ++it;
	} 
}

std::string TextProcessor::trim(std::string word) {
	word.erase(0,word.find_first_not_of(" \n\r\t"));
    word.erase(word.find_last_not_of(" \n\r\t")+1);
	return word;
}