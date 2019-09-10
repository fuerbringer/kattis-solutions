#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main(const int argc, const char* argv[]) {
  std::size_t n = 0; // num participants
  std::size_t p = 0; // points required
  std::size_t m = 0; // score entries
  std::unordered_map<std::string, std::size_t> scores;
  std::vector<std::string> winners;

  std::cin >> n >> p >> m;

  for(std::size_t i = 0; i < n; i++) {
    std::string player_name;
    std::cin >> player_name;
    scores[player_name] = 0;
  }

  for(std::size_t i = 0; i < m; i++) {
    std::string player_name;
    std::size_t score;
    std::cin >> player_name >> score;
    scores[player_name] += score;

    if(scores[player_name] >= p) {
      if(std::find(winners.begin(), winners.end(), player_name) == winners.end()) {
        winners.push_back(player_name);
      }
    }
  }

  if(winners.size()) {
    for(const auto winner : winners) {
      std::cout << winner << " wins!" << std::endl;
    }
  } else {
      std::cout << "No winner!" << std::endl;
  }

  return 0;
}
