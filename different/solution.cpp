#include <iostream>
#include <cstdint>
#include <cmath>

int main(int argc, char** argv) {
  std::uint64_t a, b;
  while(std::cin >> a >> b) {
    const std::int64_t c = a - b;
    const std::uint64_t cAbs = std::fabs(c);
    std::cout << cAbs << std::endl;
  }
  return 0;
}
