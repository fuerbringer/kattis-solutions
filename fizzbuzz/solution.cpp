#include <iostream>

int main(int argc, char** argv) {
  unsigned int X, Y, N;
  std::cin >> X >> Y >> N;
  for(std::size_t i = 1; i <= N; i++) {
    std::string out;
    if(i % X == 0) {
      out = "Fizz";
    }
    if(i % Y == 0) {
      out = "Buzz";
    }
    if(i % (X * Y) == 0) {
      out = "FizzBuzz";
    }
    if(!out.length()) {
      out = std::to_string(i);
    }
    std::cout << out << std::endl;
  }
  return 0;
}
