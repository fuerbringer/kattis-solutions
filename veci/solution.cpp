#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  std::uint32_t A;
  std::cin >> A;
  const std::string aString = std::to_string(A);
  std::string aStringSorted = aString;
  std::sort(aStringSorted.begin(), aStringSorted.end());
  std::string resultString = "0";

  /*
   *  upperExponent     = "156".length() = 3
   *  10^nextExponent   = 1000
   */
  const std::uint32_t upperExponent = aString.length();
  const std::uint32_t upper = std::pow(10, upperExponent);
  for(std::uint32_t i = A + 1; i < upper && resultString == "0"; i++) {
    const std::string iString = std::to_string(i);
    std::string iStringSorted = iString;
    std::sort(iStringSorted.begin(), iStringSorted.end());
    if(aStringSorted == iStringSorted) {
      resultString = iString;
    }
  }
  std::cout << resultString << std::endl;
  return EXIT_SUCCESS;
}
