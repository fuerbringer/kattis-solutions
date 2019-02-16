/* Challenge solution for : https://open.kattis.com/problems/measurement */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  UNKNOWN = -1,
  DESCENDING,
  ASCENDING
};

/* Doubly-linked list for storing the measurements*/
struct measurement {
  char* name;
  char* name_full;
  unsigned val_for_next; /* how much this measurement is equal for the next
                               measurement */
  struct measurement* next;
  struct measurement* prev;
};

struct measurement*
create_measurement(const char* name, const char* name_full, unsigned
    val_for_next, struct measurement* prev) {
  struct measurement* mm = 
    (struct measurement*)malloc(sizeof(struct measurement));
  if(!mm) {
    printf("Failed to malloc measurement structure");
    exit(EXIT_FAILURE);
  }
  mm->name = (char*)malloc(sizeof(char) * strlen(name));
  if(!mm->name) {
    printf("Failed to malloc name field in measurement structure");
    exit(EXIT_FAILURE);
  }
  mm->name_full = (char*)malloc(sizeof(char) * strlen(name_full));
  if(!mm->name_full) {
    printf("Failed to malloc name_full field in measurement structure");
    exit(EXIT_FAILURE);
  }
  strncpy(mm->name, name, strlen(name));
  strncpy(mm->name_full, name_full, strlen(name_full));
  mm->val_for_next = val_for_next;
  mm->next = NULL;
  mm->prev = prev;
  return mm;
}

void
destroy_measurement(struct measurement* mm) {
  free(mm->name);
  free(mm->name_full);
  free(mm);
}

void
destroy_measurements(struct measurement* start) {
  struct measurement* current = start; /* to be destroyed */
  struct measurement* next = start->next; /* to be destroyed */
  destroy_measurement(start);
  while(next) {
    current = next;
    next = next->next;
    destroy_measurement(current);
  }
}

/**
 * Find measurement by name OR full_name
 */
struct measurement*
find_measurement(char* name,
    struct measurement* start /* start of the linked list*/ ) {
  struct measurement* cur = start;
  size_t n = strlen(name);
  while(cur) {
    if(strncmp(cur->name, name, n) == 0 || 
        strncmp(cur->name_full, name, n) == 0) {
      return cur;
    }
    cur = cur->next;
  }
  return NULL;
}

/**
 * Get direction for traversing linked list
 */
int
getRelativeListDirection(struct measurement* m1, struct measurement* m2) {
  if(!m1->next) {
    /* Must be previous element if we're at the tail of the linked-list */
    return DESCENDING;
  }
  /* go with next (ascending) */
  struct measurement* cur = m1->next;
  while(cur) {
    if(cur == m2) 
      return ASCENDING;
    if(cur->next) {
      cur = cur->next;
    } else {
      /* Element is presumably in one of m1's prev elements. Fast, but potentially
       * bug-ridden outside of the scope of this Kattis Problem. */
      return DESCENDING;
    }
  }
  return UNKNOWN;
}

double
convert(unsigned source_len, struct measurement* source,
    struct measurement* dest) {
  double prod = source_len;
  if(source == dest)
    return prod;

  int dir = getRelativeListDirection(source, dest);
  if(dir == DESCENDING) {
    /* We traverse the d-list from source to dest through source->prev */
    /* Example yd -> in. We will multiply for each node to descend to smaller
     * units.
     * 5 yd * 3 = 15 ft
     * 15 ft * 12 = 18 in */
    struct measurement* cur = source->prev;
    while(cur) {
      prod *= cur->val_for_next;
      cur = (cur == dest ? NULL : cur->prev);
    }
  } else if(dir == ASCENDING) {
    /* Traverse up through source->next to the next biggest units */
    struct measurement* cur = source;
    while(cur) {
      if(cur->val_for_next)
        prod /= cur->val_for_next;
      cur = (cur->next == dest ? NULL : cur->next);
    }
  }
  return prod;
}

int
main(void) {
  /* Data entry */
  struct measurement* th = create_measurement("th", "thou", 1000, NULL);
  struct measurement* in = create_measurement("in", "inch", 12, th);
  struct measurement* ft = create_measurement("ft", "foot", 3, in);
  struct measurement* yd = create_measurement("yd", "yard", 22, ft);
  struct measurement* ch = create_measurement("ch", "chain", 10, yd);
  struct measurement* fur = create_measurement("fur", "furlong", 8, ch);
  struct measurement* mi = create_measurement("mi", "mile", 3, fur);
  struct measurement* lea = create_measurement("lea", "league", 0, mi);
  th->next = in;
  in->next = ft;
  ft->next = yd;
  yd->next = ch;
  ch->next = fur;
  fur->next = mi;
  mi->next = lea;
  lea->next = NULL;
  struct measurement* starting_measurement = th;
  /* End data entry */

  const size_t ln_len = 32; /* max line length */
  char line[ln_len];
  const char* sep = " ";
  char *token;
  size_t ti = 0; /* input token index */

  unsigned source_len = 0; /* Source length */
  struct measurement* source = NULL;
  struct measurement* dest = NULL;

  /* Read one line of input */
  if(fgets(line, ln_len, stdin)) {
    token = strtok(line, sep);
    while(token) {
      /* First deal with \n before passing to find_measurement() */
      char tok[ln_len];
      strncpy(tok, token, strlen(token));
      tok[strlen(token) - 1] = '\0';

      switch(ti) {
        case 0: /* source length */
          source_len = (unsigned)atoi(token);
          break;
        case 1: /* source */
          source = (struct measurement*)find_measurement(tok,
              starting_measurement);
          break;
        case 2: /* nop */
          /* Used for the "in" keyword */
          ;
          break;
        case 3: /* dest */
          dest = (struct measurement*)find_measurement(tok, starting_measurement);
          break;
      }
      token = strtok(NULL, sep);
      ++ti;
    }

    if(source && dest) {
      double result = convert(source_len, source, dest);
      printf("%.13f\n", result);
    }
  }


  destroy_measurements(starting_measurement);
  return EXIT_SUCCESS;
}
