#include <cstdint>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  const std::string delimeter(" ");
  std::uint16_t N; 
  std::string bp;
  while(std::cin >> N) {
    while(std::cin >> bp) {
      std::size_t pos = 0;
      std::string token;
      while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
      }
    }
  }
  return 0;
}
