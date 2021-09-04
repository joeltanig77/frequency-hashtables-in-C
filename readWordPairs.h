#ifndef READWORDPAIRS_H
#define READWORDPAIRS_H


#include <stdio.h>


/*
  A function that takes in a file pointer, a hashTable and the initial size of
  the hashTable and inserts the word pairs of a text file
*/

struct Node** readWordPairs(FILE *fp, struct Node **hashTable,
   int *size, int *sizeTracker, int *memChecker);

#endif
