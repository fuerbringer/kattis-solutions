#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>

int main(int argc, char** argv) {
  std::uint32_t A, I;
  std::cin >> A >> I;
  std::cout << (A * (I - 1) + 1) << std::endl;
  return 0;
}
