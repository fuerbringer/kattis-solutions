#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

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

int main(const int argc, const char** argv) {
  std::uint16_t N; // lines
  std::cin >> N;
  std::vector<std::string> out;
  do {
    std::string line;
    std::getline(std::cin, line);
    if(line.find("P=NP") != std::string::npos) {
      out.push_back("skipped");
    } else {
      std::vector<std::string> splitLine = split(line, '+');
      if(splitLine.size() == 2) {
        const int a = std::atoi(splitLine.at(0).c_str());
        const int b = std::atoi(splitLine.at(1).c_str());
        out.push_back(std::to_string(a + b));
      }
    }
  } while(N--);

  for(const std::string& line : out) {
    std::cout << line << std::endl;
  }
  return EXIT_SUCCESS;
}
