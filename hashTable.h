#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

// Team anti-typedef lol
struct Node {
  void *combined;
  struct Node * next;
  int freq;
};

/* Note: All sizes being passed in must be an address */


/*
  A function that takes in a hashTable and the size of the hashTable,
  the function returns a newHashTable that grows by a factor of three
  and a memCheck flag that is defaulted at zero.
  If any calloc fails inside growHashTable, the memchecker
  returns a int code that is then used to clean up the rest of
  the program and exit.
*/

struct Node** growHashTable(struct Node** hashTable, int *size, int *memChecker);

/*
 A function that takes in a hashTable the size of the hashTable, the
 number of items inserted into the hashTable, the node to be inserted,
 the datatype to be hashed and a memCheck flag that is defaulted at zero.
 If any calloc fails inside insertIntoHashTable, the memchecker
 returns a int code that is then used to clean up the rest of
 the program and exit. I grow the hashTable when the
 items inserted into the hashTable are half the size
 of the initial size of the hashTable.
 The reason I did this is because I did not want to keep track of collisions
 and so I just grew it with it hits this threshold.
*/

struct Node** insertIntoHashTable(struct Node **hashTable, int *size,
   int *sizeTracker, void *combined, int *memChecker);

/*
  A function that takes in the hashTable, the size of the hashTable, and a flag
  to for if we are clearing everything to exit the program. The function
  inserts a node into the hashTable using the void *combined value
*/

int cleanUpHashTable(struct Node **hashTable, int *size, int lastIterationFlag);

/*
  A function that takes in the newHashTable, the cursor of the linkedList,
  and the size of the newHashTable. The function walks the old hashTable,
  rehashes everything, and inserts it to the newHashTable. This function
  also walks the newHashTable as well
*/

int reHashWalk(struct Node** newHashTable, struct Node* cursor, int *size);


#endif
