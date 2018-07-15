#include <cmath>
#include <cstdint>
#include <iostream>

static const std::uint16_t COMPASS_MIN = 0; 
static const std::uint16_t COMPASS_MAX = 359; 

const int wrap(int position, const int min = COMPASS_MIN, const int max = COMPASS_MAX) {
  const int range_size = max - min + 1;

  if (position < min) {
    position += range_size * ((min - position) / range_size + 1);
  }

  return min + (position - min) % range_size;
}

int main(int argc, char** argv) {
  std::uint16_t current, target;
  std::cin >> current >> target;
  const int directRoute = -wrap(current - target);
  const int wrapRoute = wrap(target - current);
  if(std::abs(directRoute) < std::abs(wrapRoute)) {
    std::cout << directRoute << std::endl;
  } else {
    std::cout << wrapRoute << std::endl;
  }
  return EXIT_SUCCESS;
}
