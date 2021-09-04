#ifndef SORTHASHTABLE_H
#define SORTHASHTABLE_H


#include <stdio.h>
#include "hashTable.h"

/* Note: All sizes being passed in must be an address */

/*
  A function that takes in a hashTable, the items inserted into the hashTable,
  the size of the hashTable, and a array of pointers to be used for insertion
*/

int putAllStructsIntoArray(struct Node **hashTable, int *sizeTracker,
   int *size, struct Node **arrayOfStructs);


/*
  A function thats takes in void pointer 1 and void pointer 2 that is
  used for qsorting frequency's
*/

int compareFreq(const void *compare1, const void *compare2);


#endif
