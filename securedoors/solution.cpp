#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

static const std::string ANOMALY = "(ANOMALY)";
static const std::string STATUS_ENTRY_IN = "entry";
static const std::string STATUS_EXIT_IN = "exit";
static const std::string STATUS_ENTRY_OUT = "entered";
static const std::string STATUS_EXIT_OUT = "exited";

struct Person {
    Person(const std::string name, const std::string status, const int position) {
      this->name = name;
      this->status = status;
      this->position = position;
    }
    std::string name;
    std::string status;
    int position;
};

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

/**
 * Anomaly occurs when someone who's already entered entered again without exiting
 */
const bool hasEnteredAnomaly(const Person person, std::vector<Person> personVec) {
  bool alreadyEntered = true;
  for(std::vector<Person>::iterator it = personVec.begin(); it != personVec.end(); it++) {
    // Don't care what happens after
    if(person.position > *it.position && person.name == *it.name) {
      if(person.status == *it.status)
        return true;
    }
  }
  return false;
}

const bool hasExitedAnomaly(const Person person, const std::vector<Person> personVec) {
  bool exited = false;
  return exited;
}

int main(int argc, char** argv) {
  std::vector<Person> personLog;
  std::string logLengthStr;
  std::uint16_t logLength = 0;

  std::getline(std::cin, logLengthStr);
  logLength = std::atoi(logLengthStr.c_str());

  for(std::size_t l = 0; l < logLength; l++) {
    std::string logLine;
    std::getline(std::cin, logLine);
    std::vector<std::string> logLineSplit = split(logLine, ' ');
    if(logLineSplit.size() >= 2) {
      const std::string logLineStatus = logLineSplit.at(0);
      const std::string logLineName = logLineSplit.at(1);
      Person person(logLineStatus, logLineName, l);
      personLog.push_back(person);
    }
  }

  for(std::vector<Person>::iterator it = personVec.begin(); it != personVec.end(); it++) {
    if(*it.status == STATUS_EXIT_IN) {
      // Check if person has exited aleardy
      if(hasExitedAnomaly(*it, personVec)) {
        std::cout << *it.name << ' ' << *it.status << ' ' << ANOMALY;
      } else {
        std::cout << *it.name << ' ' << *it.status;
      }
    } else if(*it.status == STATUS_ENTRY_IN)
      if(hasEnteredAnomaly(*it, personVec)) {
        std::cout << *it.name << ' ' << *it.status << ' ' << ANOMALY;
      } else {
        std::cout << *it.name << ' ' << *it.status;
      }
  }
  return 0;
}
