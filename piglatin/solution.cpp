#include <cstdint>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

/**
 * If a word begins with a vowel (a, e, i, o, u, or y), simply add yay to the end of the word. For this problem, y is always a vowel. Examples: and → andyay, ordinary → ordinaryyay.
 */
static const std::string plVowelConvert(const std::string word) {
  const std::string suffix = "yay";
  std::string latinized = word;
  latinized += suffix;
  return latinized;
}

/**
 *  If a word begins with a consonant, take all of the letters before the first vowel and move them to the end of the word, then add ay to the end of the word. Examples: pig → igpay, there → erethay.
 */
static const std::string plConsonantConvert(const std::string word) {
  const std::string vowels = "aeiouy";
  const std::string suffix = "ay";
  std::string prefixToSuffix;
  std::string latinized = word;

  std::size_t prefixLen;
  bool foundPrefix = false;
  for(prefixLen = 0; prefixLen < word.length() && !foundPrefix; prefixLen++) {
    if(vowels.find(word[prefixLen]) == std::string::npos) {
      prefixToSuffix += word[prefixLen];
    } else {
      foundPrefix = true;
    }
  }
  if(prefixToSuffix.length()) {
    latinized.erase(latinized.begin(), latinized.begin() + prefixLen - 1);
    latinized += prefixToSuffix;
  }
  latinized += suffix;
  return latinized;
}

static const bool plBeginsWithVowel(const std::string word) {
  const std::string vowels = "aeiouy";
  for(std::size_t i = 0; i < vowels.length(); i++) {
    if(word[0] == vowels[i]) {
      return true;
    }
  }
  return false;
}

static const std::vector<std::string> splitString(const std::string line) {
  std::stringstream ss(line);
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  const std::vector<std::string> vstrings(begin, end);
  return vstrings;
}

int main(const int argc, const char** argv) {
  std::vector<std::string> lines;
  std::string line;
  bool doInput = true;
  while(doInput) {
    std::getline(std::cin, line);
    if(!line.length()) {
      doInput = false;
    } else {
      lines.push_back(line);
    }
  }

  for(std::vector<std::string>::iterator it = lines.begin(); it < lines.end(); it++) {
    // For each line in lines, split words and convert them to pig latin
    std::vector<std::string> words = splitString(*it);
    for(std::vector<std::string>::iterator wit = words.begin(); wit < words.end(); wit++) {
      std::cout << (plBeginsWithVowel(*wit) ? plVowelConvert(*wit) : plConsonantConvert(*wit)) << ' ';
    }
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}
