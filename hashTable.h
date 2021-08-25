#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

struct Node {
  char wordOne[500];
  char wordTwo[500];
  struct Node * prev;
  struct Node * next;
};




#endif
