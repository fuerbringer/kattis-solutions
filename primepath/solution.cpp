#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template<typename N>
static constexpr const bool isPrime(const N number) {
  for(N i = 2; i < number; i++) {
    if(number % i == 0) {
      return false;
    }
  }
  return true;
}

template<typename N>
static constexpr const std::vector<N> getPrimesInRange(const N from, const N to) {
  std::vector<N> primes;
  for(N i = from; i < to; i++) {
    if(isPrime(i)) {
      primes.push_back(i);
    }
  }
  return primes;
}

template<typename N>
static constexpr const std::size_t getNumberDigitDelta(const N a, const N b) {
  const std::string aStr = std::to_string(a);
  const std::string bStr = std::to_string(b);
  std::size_t delta = 0;
  if(aStr.length() == bStr.length()) {
    for(std::size_t ai = 0; ai < aStr.length(); ai++) {
      if(aStr[ai] != bStr[ai]) {
        delta++; // difference detected
      }
    }
  }
  return delta;
}

template<typename N>
static constexpr const std::size_t getMinimumCostPrime(const N from, const N to) {
  std::vector<N> primes = getPrimesInRange(from, to); // full prime range
  std::size_t minCost = 0;
  if(primes.size()) {
    for(typename std::vector<N>::iterator it = primes.begin() + 1; it != primes.end(); it++) {
      // if next found:
      minCost++;
    }
  }
  return minCost;
}

int main(const int argc, const char** argv) {
  std::vector<std::pair<const std::int32_t, const std::int32_t>> numberPairs;
  std::string testCasesStr;
  std::getline(std::cin, testCasesStr);
  const std::size_t testCases = (std::atoi(testCasesStr.c_str()));

  for(std::size_t i = 0; i < testCases; i++) {
    std::int32_t a, b;
    std::cin >> a >> b;
    numberPairs.push_back(std::make_pair(a, b));
  }

  for(std::size_t i = 0; i < numberPairs.size(); i++) {
    const auto from = numberPairs[i].first;
    const auto to = numberPairs[i].second;
    std::size_t minimalCost = 0;
    if(from != to) {
      minimalCost = getMinimumCostPrime(from, to);
    }
    std::cout << minimalCost << std::endl;
  }

  return EXIT_SUCCESS;
}
