#include <iostream>
#include <string>
#include <cstdint>

int main(const int argc, const char** argv) {
  const std::string CONVENTION_LEFT = "Left beehind.";
  const std::string CONVENTION_UNDECIDED = "Undecided.";
  const std::string CONVENTION_GO = "To the convention.";
  const std::string CONVENTION_NO_CONTACT = "Never speak again.";
  const std::uint16_t CONVENTION_NO_CONTACT_NUM = 13;
  std::string output;

  bool run = true;
  std::uint16_t sweet, sour;

  while(run) {
    std::cin >> sweet >> sour;
    if(sweet == 0 && sour == 0)
      run = false;
    else if(sweet + sour == CONVENTION_NO_CONTACT_NUM)
      output += CONVENTION_NO_CONTACT + '\n';
    else if(sweet > sour)
      output += CONVENTION_GO + '\n';
    else if(sweet < sour)
      output += CONVENTION_LEFT + '\n';
    else if(sour == sweet)
      output += CONVENTION_UNDECIDED + '\n';
  }

  std::cout << output;

  return EXIT_SUCCESS;
}
