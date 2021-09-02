#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

// Team anti-typedef lol
struct Node {
  char *combined;
  struct Node * next;
  int freq;
};


/* A function that takes in a file pointer, a hashtable and the initial size of
  the hashtable and inserts the word pairs of a text file */

struct Node** readWordPairs(FILE *fp, struct Node **hashTable,int *size,int *sizeTracker);


struct Node** growHashTable(struct Node** hashTable, int *size);


struct Node** insertIntoHashTable(struct Node **hashTable,int *size,int *sizeTracker,struct Node *node,char *combined);


int cleanUpHashTable(struct Node **hashTable, int *size);


int reHashWalk(struct Node** newHashTable,struct Node* cursor, int *size);


int putAllStructsIntoArray(struct Node **hashTable, int *sizeTracker, int *size, struct Node **arrayOfStructs);


int compareFreq(const void *compare1, const void *compare2);



#endif
