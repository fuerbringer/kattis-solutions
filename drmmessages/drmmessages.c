#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t
char_to_val(char c) {
  return c - 'A';
}

char
val_to_char(size_t n) {
  return n + 'A';
}

size_t
rot_val(char* str, size_t len) {
  size_t rot_val = 0, i = 0;
  for(; i < len; ++i) {
    rot_val += char_to_val(str[i]);
  }
  return rot_val;
}

void
rot_str(char* str, size_t len, size_t delta) {
  size_t i = 0;
  for(; i < len; ++i) {
    size_t new_val = (char_to_val(str[i]) + delta) % 26;
    char new_ch = val_to_char(new_val);
    str[i] = new_ch;
  }
}

char*
combine_strs(char* left, char* right, size_t len) {
  char* combined = (char*)malloc(sizeof(char) * len);
  size_t i = 0;
  for(; i < len; ++i) {
    size_t left_val = char_to_val(left[i]);
    size_t right_val = char_to_val(right[i]);
    size_t new_val = (left_val + right_val) % 26;
    combined[i] = val_to_char(new_val);
  }
  combined[len] = '\0';
  return combined;
}

int
main(void) {
  const size_t buffer_len = 15001;
  char buffer[buffer_len];

  if(fgets(buffer, buffer_len, stdin)) {
    const size_t input_len = strlen(buffer);
    const size_t input_sides_len = input_len / 2;
    char* left = (char*)malloc(sizeof(char) * input_sides_len);
    char* right = (char*)malloc(sizeof(char) * input_sides_len);

    memcpy(left, buffer, input_sides_len);
    memcpy(right, buffer + input_sides_len, input_sides_len);

    size_t left_rot_val = rot_val(left, input_sides_len);
    size_t right_rot_val = rot_val(right, input_sides_len);

    rot_str(left, input_sides_len, left_rot_val);
    rot_str(right, input_sides_len, right_rot_val);

    char* combined = combine_strs(left, right, input_sides_len);
    puts(combined);

    free(left);
    free(right);
    free(combined);
  }

  return EXIT_SUCCESS;
}
