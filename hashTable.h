#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

struct Node {
  char wordOne[100];
  char wordTwo[100];
  char combined[100];
  struct Node * next;
  int freq;
};


/* A function that takes in a file pointer, a hashtable and the initial size of
  the hashtable and inserts the word pairs of a text file   */
int takeInPairs(FILE *fp, struct Node **hashTable,int *size);



int cleanUpHashTable(struct Node **hashTable, int *size);


int growHashTable (struct Node** hashTable, int *size);



#endif
