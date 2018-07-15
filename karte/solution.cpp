#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <cstring>
#include <vector>

static const char* SAME_CARD_STR = "GRESKA";
static const char* CARD_SUITS = "PKHT";

class Card {
  private:
    std::string label;
    char suit;
    int number;

    void parsePropertiesFromString(const std::string label) {
      this->label = label;
      this->suit = label.substr(0, 1).at(0);
      this->number = std::atoi(label.substr(1, 2).c_str()); 
    }
  public:
    static const int CARD_NUM_MIN = 1;
    static const int CARD_NUM_MAX = 13;

    static std::vector<Card> generateCardsFromString(const std::string cards) {
      std::vector<Card> cardsVec;
      for(std::size_t i = 0; i < cards.length(); i += 3) {
        Card tempCard(cards.substr(i, 3));
        cardsVec.push_back(tempCard);
      }
      return cardsVec;
    }

    static std::array<int, 4> generateMissingCards(std::vector<Card> cards) {
      std::array<int, 4> missing = { CARD_NUM_MAX, CARD_NUM_MAX, CARD_NUM_MAX, CARD_NUM_MAX,  };
      for(std::size_t i = 0; i < 4; i++) {
        for(auto card : cards) {
          if(card.getSuit() == CARD_SUITS[i]) {
            missing[i]--;
          }
        }
      }
      return missing;
    }

    static const size_t generateDuplicateCount(std::vector<Card> cards) {
      std::size_t dupes = 0;
      for(std::size_t i = 0; i < cards.size(); i++) {
        Card currentCard = cards.at(i);
        for(std::size_t y = 0; y < cards.size(); y++) {
          Card tempCard = cards.at(y);
          if(i != y) {
            if(currentCard.getSuit() == tempCard.getSuit() && currentCard.getNumber() == tempCard.getNumber()) {
              dupes++;
            }
          }
        }
      }
      return dupes;
    }

    Card(const std::string label) {
      this->parsePropertiesFromString(label);
    }

    const std::string getLabel() const {
      return this->label;
    }

    const char getSuit() const {
      return this->suit;
    }

    const int getNumber() const {
      return this->number;
    }
};

int main(int argc, char** argv) {
  std::string cardsStr; // S, card labels
  std::getline(std::cin, cardsStr);
  std::vector<Card> cards = Card::generateCardsFromString(cardsStr);
  std::array<int, 4> missing = Card::generateMissingCards(cards);
  std::size_t dupes = Card::generateDuplicateCount(cards);
  if(dupes == 2) {
    std::cout << SAME_CARD_STR << std::endl;
  } else {
    for(int m = 0; m < 4; m++) {
      // suit = CARD_SUITS[m]
      if(m != 3) {
        std::cout << missing[m] << ' ';
      } else {
        std::cout << missing[m];
      }
    }
  }
  return 0;
}
