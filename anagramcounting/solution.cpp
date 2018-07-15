#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

static void swap(std::string& str, const std::size_t aPos, const std::size_t bPos) {
  char swapChar = str[aPos];
  str[aPos] = str[bPos];
  str[bPos] = swapChar;
}

static void doPermutation(std::string& str, const std::size_t index, std::size_t& counts) {
  if(index <= 0) {
  } else {
    doPermutation(str, index - 1, counts);
    std::size_t current = str.length() - index;
    for(std::size_t i = current + 1; i < str.length(); i++) {
      counts++;
      swap(str, current, i);
      doPermutation(str, index - 1, counts);
      swap(str, i, current);
    }
  }
}

int main(const int argc, const char** argv) {
  std::string str = "abcdefghijklmnopqrstuvwxyz";
  std::size_t counts = 1;
  doPermutation(str, str.length(), counts);
  std::cout << counts << std::endl;
  return EXIT_SUCCESS;
}
