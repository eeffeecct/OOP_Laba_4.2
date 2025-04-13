#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>


bool isRussian(const unsigned char& c) {
	return (c >= 0xC0 && c <= 0xFF) || c == 0xA8 || c == 0xB8;
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


void printLiteratureWithNumiration(const std::vector<std::string>& literature) {
	std::for_each(literature.begin(), literature.end(), [](const std::string& line) 
		{
			std::cout << line << std::endl;
		});
}


void printLiteratureWithoutNumiration(const std::vector<std::string>& literature) {
	int k = 1;
	std::for_each(literature.begin(), literature.end(), [&k](const std::string& line)
		{
			std::cout << k++ << ". " << line << std::endl;
		});
}


bool compare(const std::string& a, const std::string& b) {
	bool a_ = isRussian(a[0]);
	bool b_ = isRussian(b[0]);

	if (a_ != b_) {
		return a_ > b_;  
	}
	return a < b;
}


std::vector<std::string> sortByLanguage(const std::vector<std::string>& literature) {
	// create new sort vector 1) rus 2) eng
	std::vector<std::string> russianLiterature;
	std::vector<std::string> englishLiterature;
	std::for_each(literature.begin(), literature.end(), [&russianLiterature, &englishLiterature](const std::string& line)
		{
			if (!line.empty()) {
				if (isRussian(line[0])) {
					russianLiterature.push_back(line);
				}
				else {
					englishLiterature.push_back(line);
				}
			}
		});

	std::sort(russianLiterature.begin(), russianLiterature.end(), compare);
	std::sort(englishLiterature.begin(), englishLiterature.end(), compare);

	russianLiterature.insert(russianLiterature.end(), englishLiterature.begin(), englishLiterature.end());

	return russianLiterature;
}

int main() {
	std::vector<std::string> literature = readFile("text.txt");

	removeNumberPrefix(literature);

	std::vector<std::string> sortedLiterature = sortByLanguage(literature);
	printLiteratureWithNumiration(sortedLiterature); 
	std::cout << std::endl;
	printLiteratureWithoutNumiration(sortedLiterature);
}