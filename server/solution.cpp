#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
  std::uint8_t n; 
  std::uint16_t T; 
  std::string nT;
  std::string ints;

  while(std::cin >> nT) {
  }

  while(std::cin >> ints) {
    std::uint16_t timeUsed = 0;
    std::size_t usedCount = 0;
    std::stringstream streamInts;
    streamInts << ints;

    while(streamInts.good()) {
      std::string subString;
      std::getline(streamInts, subString, ' ');
      int token = std::atoi(subString.c_str());
      if(timeUsed + token >= T) {
        // Can't do any more
        std::cout << usedCount << std::endl;
      } else {
        timeUsed += token;
        usedCount++;
      }
    }
  }
  return 0;
}
