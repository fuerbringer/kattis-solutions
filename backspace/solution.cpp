#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

inline static const std::string execBackspaces(std::string line) {
  const char backspace = '<';
  for(std::size_t i = 1; i < line.length(); i++) {
    if(line[i] == backspace) {
      line.erase(i - 1, 2);
      i = 0;
    }
  }
  return line;
}

int main(const int argc, const char** argv) {
  std::string line;
  std::getline(std::cin, line);
  std::cout << execBackspaces(line) << std::endl;
  return EXIT_SUCCESS;
}

