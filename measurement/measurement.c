#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct measurement {
  char* name;
  char* name_full;
  unsigned val_for_next; /* how much this measurement is equal for the next
                               measurement */
  struct measurement* next;
  struct measurement* prev;
};

struct measurement*
create_measurement(const char* name, const char* name_full, unsigned val_for_next, struct measurement* prev) {
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
    if(strncmp(cur->name, name, n) == 0 || strncmp(cur->name_full, name, n) == 0) {
      return cur;
    }
    cur = cur->next;
  }
  return NULL;
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
  /* End data entry */

  const size_t ln_len = 32; /* max line length */
  char line[ln_len];
  const char* sep = " ";
  char *token;
  size_t ti = 0; /* input token index*/

  unsigned source_len = 0; /* Source length */
  struct measurement* source;
  struct measurement* dest;

  fgets(line, ln_len, stdin); /* Read one line of input */

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
      source = (struct measurement*)find_measurement(tok, th);
      break;
    case 2: /* nop */
      ;
      break;
    case 3: /* dest */
      dest = (struct measurement*)find_measurement(tok, th);
      break;
    }
    token = strtok(NULL, sep);
    ++ti;
  }



  printf("source_len=%d\nsource='%s'\ndest='%s'", source_len, source->name, dest->name);

  destroy_measurements(th);
  return EXIT_SUCCESS;
}
