#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Pick the largest integer in a buffer and park it 'picked'.
 */
int
pickLargest(int* buf, size_t len) {
  const int usedFlag = (-1);
  int largest = 0;
  size_t lastIndex = 0;
  for(int i = 0; i < len; i++) {
    if(buf[i] != usedFlag && (i == 0 || buf[i] > largest)) {
      largest = buf[i];
      lastIndex = i;
    }
  }
  buf[lastIndex] = usedFlag;
  return largest;
}

int
main(void) {
  int totals[2] = { /* Alice: */ 0, /* Bob: */ 0 };
  int* piecesBuff;
  size_t itok = 0;
  const char* delim = " ";
  char* tokens;
  char* lnCount; // User str pieces count
  char* lnPieces; // User str pieces
  size_t lenCount = 0;
  size_t lenPieces = 0;
  size_t pieces = 0; // Pieces count defined by user
  ssize_t nReadCount = getline(&lnCount, &lenCount, stdin);
  ssize_t nReadPieces = getline(&lnPieces, &lenPieces, stdin);

  pieces = atoi(lnCount);
  piecesBuff = malloc(sizeof(int) * pieces);
  tokens = strtok(lnPieces, delim);

  // Place user supplied pieces/tokens in a buffer
  while(tokens != NULL && pieces--) {
    piecesBuff[itok++] = atoi(tokens);
    tokens = strtok(NULL, delim);
  }

  // Alternate between alice and bob, adding the largest piece each round
  for(size_t i = 0; i < itok; i++) {
    const int person = !(i % 2 == 0);
    int piece = pickLargest(piecesBuff, itok);
    totals[person] += piece;
  }
  printf("%d %d\n", totals[0], totals[1]);

  free(lnCount);
  free(lnPieces);
  free(piecesBuff);
  return EXIT_SUCCESS;
}
