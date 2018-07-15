#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
  std::string N;
  std::vector<std::string> results;
  std::getline(std::cin, N);
  for(std::size_t i = 0; i < static_cast<std::size_t>(std::atoi(N.c_str())); i++) {
    std::string phrase;
    if(std::getline(std::cin, phrase)) {
      std::string missing;
      for(std::size_t c = 65; c <= 90; c++) {
        const char c1 = c, c2 = c + 32;
        if (phrase.find(c1) == std::string::npos && phrase.find(c2) == std::string::npos)
          missing += c2;
      }
      if(missing.length()) {
        std::string missingString;
        missingString += "missing ";
        missingString += missing;
        results.push_back(missingString);
      } else {
        results.push_back("pangram");
      }
    }
  }
  for(std::string s : results)
    std::cout << s << std::endl;
  return 0;
}
