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

int takeInPairs(FILE *fp, struct Node *hashTable,int size);


#endif
