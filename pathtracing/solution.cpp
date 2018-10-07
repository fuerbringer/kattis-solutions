#include <iostream>
#include <string>
#include <vector>

struct move {
  int dx = 0;
  int dy = 0;

  const bool isLeft() const {
    return dx == -1;
  }
  const bool isRight() const {
    return dx == 1;
  }
  const bool isUp() const {
    return dy == -1;
  }
  const bool isDown() const {
    return dy == 1;
  }
};

struct point {
  int x = 0;
  int y = 0;
};

/**
 * direction:
 *   1  -> right
 *  -1  -> left
 */
void readjustStr(const int direction, std::string* str) {
  if(direction == 1) {
    str->append(" ");
  } else if(direction == -1) {
    str->insert(0, " ");
  }
}

void readjustMatrix(const int dir, const std::size_t newLen, std::vector<std::string>* matrix) {
  for(std::string& l : *matrix) {
    if(l.length() != newLen) {
      readjustStr(dir, &l);
    }
  }
}

void printPadding(const std::size_t len, const char sym = '#') {
  for(std::size_t i = 0; i < len; i++) {
    std::cout << sym;
  }
  std::cout << std::endl;
}

int main(const int argc, const char** argv) {
  std::size_t processed = 0;
  point curPt{0, 0};
  bool done;
  std::string line;
  std::vector<move> lines;
  std::vector<std::string> matrix;

  std::getline(std::cin, line);
  do {
    if(!(done = std::cin.eof())) {
      if(line == "left")
	lines.push_back(move{-1, 0});
      if(line == "right")
	lines.push_back(move{+1, 0});
      if(line == "up")
	lines.push_back(move{0, -1});
      if(line == "down")
	lines.push_back(move{0, +1});
    }
  } while(!done && std::getline(std::cin, line));

  for(auto m : lines) {
    const std::size_t matrixLenX = matrix[0].length();
    const std::size_t matrixLenY = matrix.size();
    const std::string pathChar = (processed == lines.size() - 1 ? "E" : "*");
    // First process
    if(processed == 0) {
      if(m.isLeft()) {
	matrix.push_back("*S");
	curPt.x = 0;
	curPt.y = 0;
      }
      if(m.isRight()) {
	matrix.push_back("S*");
	curPt.x = 1;
	curPt.y = 0;
      }
      if(m.isUp()) {
	matrix.push_back("*");
	matrix.push_back("S");
	curPt.x = 0;
	curPt.y = 0;
      }
      if(m.isDown()) {
	matrix.push_back("S");
	matrix.push_back("*");
	curPt.x = 0;
	curPt.y = 1;
      }
    } else {
      if(m.isLeft()) {
	// Prepend 's' to matrix[curPt.y]
	if(matrix[curPt.y].length() >= 2) {
	  //matrix[curPt.y][(curPt.x > 0 ? curPt.x - 1 : curPt.x)] = pathChar[0];
	  matrix[curPt.y].insert(curPt.x, pathChar);
	} else {
	  matrix[curPt.y].insert(curPt.x, pathChar);
	}
	readjustMatrix(-1, matrix[curPt.y].length(), &matrix);
	curPt.x -= (curPt.x == 0 ? 0 : 1);
      }
      if(m.isRight()) {
	// Append 's' to matrix[curPt.y]
	matrix[curPt.y].insert(curPt.x + 1, pathChar);
	readjustMatrix(1, (matrix[curPt.y].length()), &matrix);
	curPt.x++;
      }
      if(m.isUp()) {
	// Pad and Push before if (curPt.y == 0)
	if(curPt.y == 0) {
	  std::string newStr;
	  for(std::size_t i = 0; i < matrix[0].length(); i++) {
	    if(i != static_cast<std::size_t>(curPt.x)) {
	      newStr.append(" ");
	    } else {
	      newStr.append(pathChar);
	    }
	  }
	  matrix.insert(matrix.begin(), newStr);
	} else {
	  matrix[curPt.y - 1][curPt.x] = pathChar[0];
	  curPt.y--;
	}
      }
      if(m.isDown()) {
	// Pad and Push before if (curPt.y == matrix.size() - 1)
	if(static_cast<std::size_t>(curPt.y) == matrix.size() - 1) {
	  std::string newStr;
	  for(std::size_t i = 0; i < matrix[0].length(); i++) {
	    if(i != static_cast<std::size_t>(curPt.x))
	      newStr.append(" ");
	    else
	      newStr.append(pathChar);
	  }
	  matrix.push_back(newStr);
	} else {
	  matrix[curPt.y + 1][curPt.x] = pathChar[0];
	}
	curPt.y++;
      }
      //std::cout << '(' << curPt.x << '/' << curPt.y << ')' << std::endl;
    }
    processed++;
  }


  printPadding(matrix[0].size() + 2);
  for(auto l : matrix) {
    std::cout << '#' << l << '#' << std::endl;
  }
  printPadding(matrix[0].size() + 2);

  return EXIT_SUCCESS;
}
