#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define LINES 7
#define MAX_DIGIT_WIDTH 5
#define MAX_TOTAL_ASCII_DIGITS (9 + 9 + 1)
#define MAX_TOTAL_CHARS_LINE (MAX_DIGIT_WIDTH * MAX_TOTAL_ASCII_DIGITS)
#define MAX_SINGLE_DIGIT_CHARS (LINES * MAX_DIGIT_WIDTH)

static const char* asciiDigits[][LINES] = {
  {
    "xxxxx",
    "x...x",
    "x...x",
    "x...x",
    "x...x",
    "x...x",
    "xxxxx"
  }, {
    "....x",
    "....x",
    "....x",
    "....x",
    "....x",
    "....x",
    "....x"
  }, {
    "xxxxx",
    "....x",
    "....x",
    "xxxxx",
    "x....",
    "x....",
    "xxxxx"
  }, {
    "xxxxx",
    "....x",
    "....x",
    "xxxxx",
    "....x",
    "....x",
    "xxxxx"
  }, {
    "x...x",
    "x...x",
    "x...x",
    "xxxxx",
    "....x",
    "....x",
    "....x"
  }, {
    "xxxxx",
    "x....",
    "x....",
    "xxxxx",
    "....x",
    "....x",
    "xxxxx"
  }, {
    "xxxxx",
    "x....",
    "x....",
    "xxxxx",
    "x...x",
    "x...x",
    "xxxxx"
  }, {
    "xxxxx",
    "....x",
    "....x",
    "....x",
    "....x",
    "....x",
    "....x"
  }, {
    "xxxxx",
    "x...x",
    "x...x",
    "xxxxx",
    "x...x",
    "x...x",
    "xxxxx"
  }, {
    "xxxxx",
    "x...x",
    "x...x",
    "xxxxx",
    "....x",
    "....x",
    "xxxxx"
  }, {
   ".....",
   "..x..",
   "..x..",
   "xxxxx",
   "..x..",
   "..x..",
   "....."
  }
};

void readLines(char buffer[LINES][MAX_TOTAL_CHARS_LINE]) {
  for(size_t i = 0; i < LINES;) {
    char* eof = fgets(buffer[i], sizeof(buffer[i]), stdin);
    if(eof) i++;
  }
}

/*
 * Parses ASCII digits from asciiDigits stacked side-by-side.
 * Returns an array of indices for asciiDigits
 */
void parseAsciiDigits(char input[LINES][MAX_TOTAL_CHARS_LINE], size_t output[MAX_TOTAL_ASCII_DIGITS]) {
  for(size_t x = 0; x < MAX_TOTAL_CHARS_LINE; x += MAX_DIGIT_WIDTH) {
    for(size_t y = 0; y < LINES; y++) {
      char userBuffer[MAX_SINGLE_DIGIT_CHARS];
    }
  }
}

int main(const int argc, const char* argv[]) {
  char linesBuf[LINES][MAX_TOTAL_CHARS_LINE];
  readLines(linesBuf);
  return EXIT_SUCCESS;
}
