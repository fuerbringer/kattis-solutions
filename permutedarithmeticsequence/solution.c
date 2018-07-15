#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int32_t main(const int32_t argc, const char* argv[]) {
  char line[100 * 3] = { '\0' };
  int32_t lines; // count of datasets
  scanf("%d", &lines);
  do {
    printf("\n[--%s--%d--]\n", line, lines);
  } while(fgets(line, sizeof(line) - 1, stdin) && lines--);
  return EXIT_SUCCESS;
}
