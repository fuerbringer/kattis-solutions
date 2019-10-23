/* Challenge solution for : https://open.kattis.com/problems/runlengthencodingrun */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decode(char* input, const size_t input_len) {
  size_t i = 2;
  for(; i < input_len; i++) {
    if(!(input[i] >= 48 && input[i] <= 57)) {
      if(i + 1 < input_len) {
        int n = input[i + 1] - '0';
        while(n--) {
          putchar(input[i]);
        }
      }
    }
  }
  putchar('\n');
}

void encode(char* input, const size_t input_len) {
  size_t i = 3, streak = 1;
  char last_chr = input[2];
  for(; i < input_len; i++) {
    if(last_chr == input[i]) {
      streak++;
    } else {
      char pc = streak + '0';
      putchar(last_chr);
      putchar(pc);
      streak = 1;
    }
    last_chr = input[i];
  }
  putchar('\n');
}

int
main(void) {
  const size_t input_len = 100 + 2;
  char input[input_len];
  char* result = NULL;

  if(fgets(input, input_len, stdin)) {
    switch(input[0]) {
      case 'E':
        encode(input, strlen(input));
        break;
      case 'D':
        decode(input, strlen(input));
        break;
    }
  }

  if(result) {
    printf("%s\n", result);
  }

  return EXIT_SUCCESS;
}
