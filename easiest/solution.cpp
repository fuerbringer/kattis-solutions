#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

static const int digitSum(const int d) {
  int sum = 0;
  const std::string dStr(std::to_string(d));
  for(const auto chr : dStr) {
    sum += static_cast<int>(chr - 48);
  }
  return sum;
}

int main(int argc, char** argv) {
  const int pMin = 10;
  bool ok = true;
  std::string in;
  std::vector<int> ps;
  do {
    std::getline(std::cin, in);
    if((ok = in != "0")) {
      const int N = static_cast<int>(std::atoi(in.c_str()));
      const int digitSumN = digitSum(N);
      bool foundMin = false;
      for(int p = pMin; p <= INT32_MAX && !foundMin; p++) {
        const int digitSumP = digitSum(N * p);
        if(digitSumP == digitSumN && p > pMin) {
          ps.push_back(p);
          foundMin = true;
        }
      }
    }
  } while(ok);
  for(const auto p : ps) {
    std::cout << p << std::endl;
  }
  return 0;
}
