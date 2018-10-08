#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
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

int main(const int argc, const char** argv) {
  std::unordered_map<std::string, int> definesMap;
  std::vector<std::string> outLog;
  std::string line;

  while(std::getline(std::cin, line) && !std::cin.eof()) {
    std::vector<std::string> splitLine = split(line, ' ');
    if(splitLine.size()) {
      if(splitLine[0] == "define") {
	if(splitLine.size() == 3) {
	  definesMap[splitLine[2]] = std::atoi(splitLine[1].c_str());
	}
      }
      if(splitLine[0] == "eval") {
	if(splitLine.size() == 4) {
	  int evaluation = -1;
	  // 1 -> lvalue
	  // 2 -> operator
	  // 3 -> rvalue
	  if(definesMap.count(splitLine[1]) > 0 && definesMap.count(splitLine[3]) > 0) {
	    if(splitLine[2] == "=") {
	      evaluation = (definesMap[splitLine[1]] == definesMap[splitLine[3]]);
	    }
	    if(splitLine[2] == ">") {
	      evaluation = (definesMap[splitLine[1]] > definesMap[splitLine[3]]);
	    }
	    if(splitLine[2] == "<") {
	      evaluation = (definesMap[splitLine[1]] < definesMap[splitLine[3]]);
	    }
	  }
	  switch(evaluation) {
	    case 0: outLog.push_back("false"); break;
	    case 1: outLog.push_back("true"); break;
	    case -1: outLog.push_back("undefined"); break;
	  }
	}
      }
    }
  }

  for(auto logEntry : outLog) {
    std::cout << logEntry << std::endl;
  }
  return EXIT_SUCCESS;
}
