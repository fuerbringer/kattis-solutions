#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main(const int argCount, const char* args[]) {
  std::string numCasesStr;
  std::getline(std::cin, numCasesStr);
  const std::size_t numCases= std::atoi(numCasesStr.c_str());
  std::vector<std::vector<std::string>> cases;

  for(std::size_t i = 0; i < numCases; i++) {
    std::vector<std::string> caseVec;
    std::size_t x = 0, y = 0;
    std::cin >> x >> y;
    for(std::size_t z = 0; z < y; z++) {
      std::string line;
      std::cin >> line;
      line.resize(x);
      std::reverse(line.begin(), line.end()); // reverse on x-axis
      caseVec.push_back(line);
    }
    std::reverse(caseVec.begin(), caseVec.end()); // reverse on y-axis
    cases.push_back(caseVec);
  }

  std::size_t testCounter = 1;
  for(const auto& caseVec : cases) {
    std::cout << "Test " << testCounter << std::endl;
    for(const auto& line : caseVec) {
      std::cout << line << std::endl;
    }
    testCounter++;
  }

  return EXIT_SUCCESS;
}
