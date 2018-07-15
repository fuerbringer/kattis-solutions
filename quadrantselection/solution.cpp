#include <iostream>
#include <cstdint>

int main(const int argc, const char** argv) {
  std::int16_t x, y;
  std::cin >> x >> y;
  if(x > 0 && y > 0)
    std::cout << 1;
  else if(x < 0 && y > 0)
    std::cout << 2;
  else if(x < 0 && y < 0)
    std::cout << 3;
  else if(x > 0 && y < 0)
    std::cout << 4;
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
