#include "utils.h"
#include <string>
#include <vector>

std::vector<std::string> split(std::string& text, std::string& delimiter) {
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