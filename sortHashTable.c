#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashTable.h"
#include "readWordPairs.h"
#include "sortHashTable.h"


int compareFreq(const void *compare1,const void *compare2) {
    // Cast to double pointer then defererence twice to compare actual values
    struct Node **node1 = (struct Node **)compare1;
    struct Node **node2 = (struct Node **)compare2;
    return (*node2)->freq - (*node1)->freq;
}


int putAllStructsIntoArray(struct Node **hashTable,int *sizeTracker,int *size,
  struct Node **arrayOfStructs) {
  int j = 0;
  int sizeOfItems = *size;
  for (int i = 0; i < sizeOfItems; i++) {
      // Iterate the array of linked lists
      if(hashTable[i] != NULL) {
        struct Node* cursor = hashTable[i];
        if(cursor->next == NULL) {
            while(arrayOfStructs[j] != NULL) {
              j++;
            }
            // Array of structs should be empty here
            arrayOfStructs[j] = hashTable[i];
            continue;
        }
        while(cursor->next != NULL) {
          while(arrayOfStructs[j] != NULL) {
            j++;
          }
            // Array of structs should be empty here
            arrayOfStructs[j] = cursor;
            cursor = cursor->next;
        }
        // If cursor->next == NULL insert the last cursor
        j++;
        arrayOfStructs[j] = cursor;
      }
  }
    return 0;
}
