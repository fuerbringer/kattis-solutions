#include <iostream>
#include <string>
#include <cmath>

static const char* responses[2] = { "Diablo is happy!", "Need more materials!" };

int main(const int argc, const char* argv[]) {
  float A = 0, N = 0;
  std::cin >> A >> N;
  const float sqMeters = (N / 2) * (N / 2);

  std::cout << responses[static_cast<std::size_t>(sqMeters == A || !N)] << std::endl;

  return EXIT_SUCCESS;
}
