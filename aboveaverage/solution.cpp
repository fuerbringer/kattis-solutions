#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

const double averageFromVector(std::vector<std::string> vector) {
  int sum = 0;
  for(std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++) {
    std::string tempToken = *it;
    sum += std::atoi(tempToken.c_str());
  }
  return (sum / vector.size());
}

int main(const int argc, const char** argv) {
  std::vector<std::vector<std::string>> lines;
  std::uint8_t N; // Number of cases
  std::string nStr;
  std::cout.precision(3);
  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::getline(std::cin, nStr);

  N = std::atoi(nStr.c_str());
  do {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> lineTokens = split(line, ' ');
    if(lineTokens.size() >= 2) {
      lines.push_back(lineTokens);
    }
  } while(--N);

  for(auto lineTokens : lines) {
    const double classSize = lineTokens.size() - 1;
    const double avg = averageFromVector(std::vector<std::string>(lineTokens.begin() + 1, lineTokens.end()));
    double aboveAvg = 0;
    for(std::vector<std::string>::iterator it = lineTokens.begin() + 1; it != lineTokens.end(); it++) {
      std::string tempToken = *it;
      const int grade = std::atoi(tempToken.c_str());
      if(grade > avg) {
        aboveAvg++;
      }
    }
    std::cout << ((aboveAvg / classSize) * 100) << '%' << std::endl;
  }
  return EXIT_SUCCESS;
}
