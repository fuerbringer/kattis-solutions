#include<iostream>
#include<string>
#include<vector>

std::size_t dancerCount(std::vector<std::string> lines) {
	if(!lines.size())
		return 0;

	// Assume first lines str len is the rest of its elements
	const std::size_t lineLength = lines[0].length();
	const std::size_t lineCount = lines.size();
	std::size_t dancers = 0;

	for(std::size_t x = 0; x < lineLength; x++) {
		std::size_t nonEmpties = 0;
		for(std::size_t y = 0; y < lineCount; y++) {
			const char ch = lines[y][x];
			if(ch == '$') {
				++nonEmpties;
			}
		}
		if(nonEmpties == 0) {
			++dancers;
		}
	}
	return 1 + dancers;
}

int main(void) {
	std::vector<std::string> lines;
	std::size_t lineCount = 0, lineLength = 0;
	std::cin >> lineCount >> lineLength;
	std::cin.ignore();

	for(std::size_t i = 0; i < lineCount; i++) {
		std::string line;
		std::getline(std::cin, line);
		if(line.length() > lineLength) {
			line.erase(line.begin() + lineLength);
		}
		lines.push_back(line);
	}

	std::cout << dancerCount(lines) << std::endl;

	return 0;
}
