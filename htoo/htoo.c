#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct atom {
  /* The problem defines the Atom name as a single char (no Cl and
   * such) */
  char name;
  /* Atom count */
  size_t count;
};

struct molecule {
  /* A molecule is composed of a set of atoms */
  struct atom** atoms;
  /* Molecule count */
  size_t count;
};

struct atom* create_atom(char name, size_t count) {
  struct atom* atm = (struct atom*)malloc(sizeof(struct atom));
  if(!atm) {
    printf("Failed to malloc atom structure");
    exit(EXIT_FAILURE);
  }
  atm->name = name;
  atm->count = count;
  return atm; 
}

void destroy_atom(struct atom* atm) {
  free(atm);
}

struct molecule* create_molecule(size_t count, size_t initial_atom_alloc_size) {
  struct molecule* mol = (struct molecule*)malloc(sizeof(struct molecule));
  if(!mol) {
    printf("Failed to malloc molecule structure");
    exit(EXIT_FAILURE);
  }
  mol->atoms = (struct atom**)malloc(sizeof(struct atom*) * initial_atom_alloc_size);
  mol->count = count;
  return mol;
}

void destroy_molecule(struct molecule* molecule, size_t atom_count) {
  while(--atom_count) {
    destroy_atom(molecule->atoms[atom_count]);
  }
  free(molecule->atoms);
  free(molecule);
}

int /* boolean */
isDigit(char c) {
  return c >= 48 && c <= 57;
}

int 
main(void) {
  const size_t in_mol_ln = 2500 /* molecule */ + 1 /* space */ + 4 /* k */;
  char in_mol[in_mol_ln]; /* Raw stdin input */
  size_t in_molecule_atoms_size = 8, /* Alloc 8 atoms by default*/
         in_molecule_atoms_index = 0 /* Index at which we append new atoms to
                                        the molecule */;

  /* Input molecule with which we'll create the new molecule */
  struct molecule* in_molecule = create_molecule(0, in_molecule_atoms_size);

  if(fgets(in_mol, in_mol_ln, stdin)) {
    size_t in_mol_strln = strlen(in_mol), /* Raw input string length*/
           i = 0;

    for(; i < in_mol_strln && in_mol[i] != ' '; ++i) {
      if(!isDigit(in_mol[i])) {
        char new_atm_name = in_mol[i];
        size_t new_atm_count = 1; /* Atom count omitted means no digit follows */
        if(i + 1 < in_mol_strln && isDigit(in_mol[i + 1])) {
          /* Next char in input denotes how many atoms we're dealing with */
          new_atm_count = in_mol[i + 1] - '0';
        }
        struct atom* atm = create_atom(new_atm_name, new_atm_count);

        /* Make sure we don't run out of space in the alloced atoms in our
         * input molecule */
        if(in_molecule_atoms_size > in_molecule_atoms_index) {
          in_molecule_atoms_size *= 2;
          in_molecule->atoms = realloc(in_molecule->atoms, in_molecule_atoms_size);
        }
        in_molecule->atoms[in_molecule_atoms_index++] = atm;
      }
    }
  }

  size_t i = 0;
  for(; i < in_molecule_atoms_index + 1; ++i) {
    printf("(%c,%ld)\n", in_molecule->atoms[i]->name, in_molecule->atoms[i]->count);
  }

  destroy_molecule(in_molecule, in_molecule_atoms_index);
  return EXIT_SUCCESS;
}
