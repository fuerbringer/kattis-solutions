#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>

int main(int argc, char** argv) {
  std::uint16_t N;  // Number of people
  std::uint8_t T;   // Time left
  std::vector<std::pair<uint16_t, uint8_t>> cashTime;
  std::cin >> N >> T;
  for(size_t i = 0; i < N; i++) {
    std::uint32_t ci; // persons cash
    std::uint8_t ti; // persons patience in time
    std::cin >> ci >> ti;
    cashTime.push_back(std::make_pair(ci, ti));
  }
  std::sort(cashTime.begin(), cashTime.end(), [](auto &left, auto &right) {
    return left.second < right.second;
  });
  for(auto citi : cashTime) {
    std::cout << "> " << citi.first << citi.second << std::endl;
  }
  return 0;
}
