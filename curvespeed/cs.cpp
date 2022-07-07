#include <iostream>
#include <cmath>

double V(double R, double S) {
  return std::sqrt((R * (S + 0.16)) / 0.067);
}

int main(int argc, char* argv[]) {
  double R, S, res;

  while(std::cin >> R >> S) {
    res = V(R, S);
    std::cout << std::round(res) << std::endl;
  }

  return 0;
}
