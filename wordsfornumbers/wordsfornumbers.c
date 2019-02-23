/* Challenge solution for : https://open.kattis.com/problems/wordsfornumbers */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINES 100
#define TOKENS 100
#define TOKEN_LEN 15
#define LINE_LEN (TOKENS * TOKEN_LEN + 1)

/* [0, 9] */
static char* singles[] = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
};

/* [11, 19] */
static char* teens[] = {
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eighteen",
  "nineteen",
};

/* [10,90] in steps of 10 */
static char* tens[] = {
  "ten",
  "twenty",
  "thirty",
  "forty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety",
};

int
isNumeralStr(const char* token) {
  const size_t len = strlen(token);
  size_t i = 0;
  for(; i < len; i++) {
    const char c = token[i];
    if((c < 48 || c > 57) && (c != '\0' && c != '\n'))
      return 0; /* false, has chars outside of digit range */
  }
  return 1; /* token has digit chars only */
}

char*
numberToWord(int num) {
  char* str_num;
  char* str_to_cpy = NULL;
  size_t str_len = 0;
  if(num < 10) {
    str_to_cpy = singles[num];
  } else if(num > 10 && num < 20) {
    str_to_cpy = teens[num - 11];
  } else if(num % 10 == 0) {
    str_to_cpy = tens[(num / 10) - 1];
  } else {
    /* Number must be a composite number ([tens]-[singles])*/
    int single = num % 10;
    int ten = num - single;
    const char* sep = "-";
    const char* single_str = singles[single];
    const char* ten_str = tens[(ten / 10) - 1];
    const size_t sep_len = strlen(sep);
    const size_t single_len = strlen(single_str);
    const size_t ten_len = strlen(ten_str);
    str_num = calloc(single_len + ten_len + sep_len, sizeof(char));
    if(!str_num)
      goto alloc_fail;
    strncat(str_num, ten_str, ten_len);
    strncat(str_num, sep, sep_len);
    strncat(str_num, single_str, single_len);
    return str_num;
  }
  if(str_to_cpy) {
    str_len =  strlen(str_to_cpy);
    str_num = calloc(str_len, sizeof(char));
    if(!str_num)
      goto alloc_fail;
    strncpy(str_num, str_to_cpy, str_len);
    return str_num;
  }
  return NULL; /* failed to convert to word form */

alloc_fail:
  printf("numberToWord: Failed to calloc str_num. Aborting.\n");
  exit(EXIT_FAILURE);
}

int
main(void) {
  char line[LINE_LEN];
  const char* sep = " ";
  char* token;
  char** prod_str =  (char**)malloc(LINES * sizeof(char*)); /* result string */
  size_t allocated_lns = 0; /* lines that were allocated */
  size_t ti = 0; /* token index*/
  int run = 1;

  if(!prod_str)
    goto alloc_fail;

  while(run && fgets(line, LINE_LEN, stdin)) {
    if(!strlen(line)) {
      run = 0; /* Empty line */
    } else {
      token = strtok(line, sep);
      ti = 0;
      /* malloc for first token */
      while(token) {
        if(isNumeralStr(token)) {
          /* Token is a number; Allocate memory and copy into current line (prod_str) */
          char* str_num = numberToWord(atoi(token));
          if(!ti) {
            prod_str[allocated_lns] = (char*)malloc(strlen(str_num) * sizeof(char) + 1);
            if(!prod_str[allocated_lns])
              goto alloc_fail;
            /* First token AND a number (start of sentence). capitalize first letter*/
            strncpy(prod_str[allocated_lns], str_num, strlen(str_num));
          } else {
            prod_str[allocated_lns] = (char*)realloc(prod_str[allocated_lns], strlen(prod_str[allocated_lns]) * sizeof(char) + strlen(str_num) + 1);
            if(!prod_str[allocated_lns])
              goto alloc_fail;
            strncat(prod_str[allocated_lns], str_num, strlen(str_num));
          }
          strncat(prod_str[allocated_lns], sep, strlen(sep));
          free(str_num);
          str_num = NULL;
        } else {
          /* Token is a word (or anything else); Allocate memory and copy into current line (prod_str) */
          if(!ti) {
            prod_str[allocated_lns] = (char*)malloc(strlen(token) * sizeof(char) + 1);
            if(!prod_str[allocated_lns])
              goto alloc_fail;
            strncpy(prod_str[allocated_lns], token, strlen(token));
          } else {
            prod_str[allocated_lns] = (char*)realloc(prod_str[allocated_lns], strlen(prod_str[allocated_lns]) * sizeof(char) + strlen(token) + 1);
            if(!prod_str[allocated_lns])
              goto alloc_fail;
            strncat(prod_str[allocated_lns], token, strlen(token));
          }
          strncat(prod_str[allocated_lns], sep, strlen(sep));
        }
        token = strtok(NULL, sep); /* Next token */
        ++ti;
      }
      ++allocated_lns;
    }
  }

  /* Output and Cleanup */
  size_t ci = 0;
  for(; ci < allocated_lns; ci++) {
    printf("%s\n", prod_str[ci]);
    free(prod_str[ci]);
  }
  free(prod_str);
  prod_str = NULL;

  return EXIT_SUCCESS;

alloc_fail: 
  printf("main: Failed to malloc. Aborting.\n");
  exit(EXIT_FAILURE);
}
