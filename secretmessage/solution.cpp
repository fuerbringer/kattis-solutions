#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

static const std::string padString(const std::string original, const std::size_t count, const char padChar = '*') {
  std::string newString = original;
  for(std::size_t i = 0; i < count; i++) {
    newString += padChar;
  }
  return newString;
}

static const std::string encrypt(const std::string original) {
  const std::size_t L = original.length(); // original message length
  const std::size_t M = std::pow(std::ceil(std::pow(L, 0.5)), 2);
  const std::size_t K = std::sqrt(M); // table size
  const std::size_t padCount = (M - L); // padding chars needed
  const std::string paddedString = padString(original, padCount);
  std::vector<std::string> box; // rotation box
  for(std::size_t i = K; i < L; i += K) {
    std::cout << original.substr(i - K, i) << std::endl;
  }
  return "";
}

std::int32_t main(const std::int32_t argc, const char** argv) {
  std::uint8_t N; // lines count
  std::string nInput;
  std::vector<std::string> lines; // lines array
  std::getline(std::cin, nInput);
  N = std::atoi(nInput.c_str());
  for(std::size_t i = 0; i < N; i++) {
    std::string line;
    std::getline(std::cin, line);
    lines.push_back(line);
  }

  for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++) {
    std::cout << encrypt(*it) << std::endl;
  }

  return EXIT_SUCCESS;
}
