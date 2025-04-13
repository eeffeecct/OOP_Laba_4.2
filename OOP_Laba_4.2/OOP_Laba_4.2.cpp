#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>


bool isRussian(const std::string& s) {
	for (char c : s) {
		if ((c >= 'А' && c <= 'я') || c == 'ё' || c == 'Ё') {
			return true;
		}
	}
	return false;
}


void removeNumberPrefix(std::vector<std::string>& literature) {
	for (std::vector<std::string>::iterator it = literature.begin(); it != literature.end(); it++) {
		size_t dot = it->find(".");
		if (dot != std::string::npos) { 
			*it = it->substr(dot + 2);
		}
	}
}


std::vector<std::string> readFile(const std::string& filename) {
	std::vector<std::string> literature;
	std::ifstream inFile(filename);
	std::string line;

	if (!inFile.is_open()) {
		std::cerr << "Can`t open file";
		return literature;
	}

	while (std::getline(inFile, line)) { 
		if (!line.empty()) {
			literature.push_back(line);
		}
	}

	inFile.close();
	return literature;
}


void printLiterature(const std::vector<std::string>& literature) {
	std::for_each(literature.begin(), literature.end(), [](const std::string& line) 
		{
			std::cout << line << std::endl;
		});
}


std::vector<std::string> sortByLanguage(const std::vector<std::string>& literature) {
	// create new sort vector 1) rus 2) eng
	std::vector<std::string> sortLiterature;
	std::for_each(literature.begin(), literature.end(), [](const std::string& line)
		{
			if (isRussian(line[0])) {

			}
		});
}

int main() {
	std::vector<std::string> literature = readFile("text.txt");

	removeNumberPrefix(literature);
	printLiterature(literature);

	
	

}