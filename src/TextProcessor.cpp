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
	// Carrega as stopwords e as coloca em um unordered_set assim que a classe textProcessor é instanciada
	std::filesystem::path path = "stopwords.txt";
	std::string rawStopWords = readTextFile(path);
	std::vector<std::string> stopWords = split(rawStopWords, ' ');
	for (auto& word : stopWords) trim(word);

	for(auto& word : stopWords) stopWordsSet.insert(word);
}

std::unordered_set<std::string> TextProcessor::processar(std::filesystem::path path) {
	std::cout<<"\n Processando: "<<path<<"\n";
	/* 
		Lê o arquivo de texto e divide a string em um vetor de palavras, 
	   	as coloca em um set e depois diminui remove os caracteres indesejados
		e por fim exclui as palavras dentro do stopwords do set e retorna o resultado
	*/
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

	// Se não tiver nenhum problema com o arquivo, lê todo o conteúdo do arquivo e coloca em uma string

    auto size = std::filesystem::file_size(path);
    std::string content(size, '\0');
    std::ifstream in(path);
    in.read(&content[0], size);

    return content;
}

std::vector<std::string> split(std::string& text, const char& delimiter) {
	// Usa o stringstream e o getline do std para dividir o conteúdo com base no delimiter
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

	// Aqui usa o locale C.UTF-8 pra poder diminuir os caracteres com acento
    std::locale loc("C.UTF-8");

	// cria uma cópia da palavra em minúsculo e depois faz o swap dos dois
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
	// Remove palavras indesejadas do set
	while (it != text.end()) {
		bool check = *it == "\n" || *it == "";
		if (stopWordsSet.count(*it) > 0 || check) it = text.erase(it);
		else ++it;
	} 
}

// Limpa a palavra se tiver algum caracter problemático (quebra de linha e etc.)
std::string TextProcessor::trim(std::string word) {
	word.erase(0,word.find_first_not_of(" \n\r\t"));
    word.erase(word.find_last_not_of(" \n\r\t")+1);
	return word;
}