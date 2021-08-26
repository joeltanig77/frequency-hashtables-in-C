#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

struct Node {
  char *wordOne;
  char *wordTwo;
  char *combined;
  struct Node * prev;
  struct Node * next;
};


/* A function that takes in a file pointer, a hashtable and the initial size of
  the hashtable and inserts the word pairs of a text file   */
int takeInPairs(FILE *fp, struct Node **hashTable,int size);



#endif
