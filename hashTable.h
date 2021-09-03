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
  A function that takes in a file pointer, a hashTable and the initial size of
  the hashTable and inserts the word pairs of a text file
*/

struct Node** readWordPairs(FILE *fp, struct Node **hashTable,
   int *size, int *sizeTracker);

/*
  A function that takes in a hashTable and the size of the hashTable,
  the function returns a newHashTable that grows by a factor of three
*/

struct Node** growHashTable(struct Node** hashTable, int *size);

/*
 A function that takes in a hashTable the size of the hashTable, the
 number of items inserted into the hashTable, the node to be inserted and finally
 the datatype to be hashed. I grow the hashTable when the items inserted
 into the hashTable are half the size of the initial size of the hashTable.
 The reason I did this is because I did not want to keep track of collisions
 and so I just grew it hits this threshold.
*/

struct Node** insertIntoHashTable(struct Node **hashTable, int *size,
   int *sizeTracker, struct Node *node, void *combined);

/*
  A function that takes in the hashTable, the size of the hashTable, and a flag
  to for if we are clearing everything to exit the program. The function
  inserts a node into the hashTable using the void *combined value
*/

int cleanUpHashTable(struct Node **hashTable, int *size, int lastIterationFlag);

/*
  A function that takes in the newHashTable, the cursor of the linkedList,
  and the size of the newHashTable. The function walks the old hashTable,
  rehashes everything, and inserts it to the newHashTable
*/

int reHashWalk(struct Node** newHashTable, struct Node* cursor, int *size);

/*
  A function that takes in a hashTable, the items inserted into the hashTable,
  the size of the hashTable, and a array of pointers to be used for insertion
*/

int putAllStructsIntoArray(struct Node **hashTable, int *sizeTracker,
   int *size, struct Node **arrayOfStructs);

/*
  A function thats takes in void pointer 1 and void pointer 2 that that is
  used for qsorting frequency's
*/

int compareFreq(const void *compare1, const void *compare2);


#endif
