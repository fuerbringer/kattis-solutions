#include <cstdint>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <string>
#include <vector>

int main(const int argc, const char** argv) {
  const std::regex hexMatch("0[xX][0-9a-fA-F]+");
  std::vector<std::string> hexNumbers;
  std::string line;
  std::size_t max = 100;
  do {
    std::getline(std::cin, line);
    hexNumbers.push_back(line);
  } while(--max);

  for(std::string hexStr : hexNumbers) {
    for(std::sregex_iterator i = std::sregex_iterator(hexStr.begin(), hexStr.end(), hexMatch); i != std::sregex_iterator(); ++i) {
      std::smatch hex = *i;
      unsigned int hexAsInt;   
      std::stringstream ss;
      ss << std::hex << hex.str();
      ss >> hexAsInt;
      std::cout << hex.str() << ' ' << hexAsInt << '\n';
   }
  }
  return EXIT_SUCCESS;
}

