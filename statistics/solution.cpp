#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = std::atoi(item.c_str());
  }
}

std::vector<int> split(const std::string &s, char delim) {
  std::vector<int> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}


int main(int argc, char** argv) {
  std::size_t lineCount = 0;
  const std::size_t maxLineCount = 10;
  std::string line;
  std::vector<std::vector<int>> lines;
  while(std::getline(std::cin, line) && lineCount++ < maxLineCount) {
    std::vector<int> lineVec = split(line, ' ');
    lines.push_back(lineVec);
  }

  std::size_t caseLine = 1;
  for(auto line : lines) {
    const int len = line.at(0);
    const int min = *std::min_element(line.begin() + 1, line.end());
    const int max = *std::max_element(line.begin() + 1, line.end());
    const int range = max - min;

    std::cout << "Case " << caseLine << ": "
      << min << ' ' << max << ' '
      << range << std::endl;
    caseLine++;
  }

  return 0;
}
