#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"

// Cursor assign temp to then free temp then continue walk
// TODO 1: Need to do some UI stuff


int cleanUpHashTable(struct Node **hashTable, int *size, int lastIterationFlag) {
    for (int i = 0; i < *size; i++) {
        if(hashTable[i] != NULL) {
          struct Node* cursor = hashTable[i];
          struct Node* temp = NULL;
          if(cursor->next == NULL) {
            if(lastIterationFlag) {
              free(cursor->combined);
            }
              free(cursor);
              continue;
          }
          while(cursor->next != NULL) {
              temp = cursor;
              cursor = cursor->next;
              if(lastIterationFlag) {
                free(temp->combined);
              }
              free(temp);
          }
          // Free the last node
          if(lastIterationFlag) {
            free(cursor->combined);
          }
          free(cursor);
        }
    }
    return 0;
}


int compareFreq(const void *compare1,const void *compare2) {
    // Cast to double pointer then defererence twice to compare actual values
    struct Node **node1 = (struct Node **)compare1;
    struct Node **node2 = (struct Node **)compare2;
    return (*node2)->freq - (*node1)->freq;
}


struct Node** growHashTable (struct Node** hashTable, int *size) {
    // Growing the hashTable by a factor of three
    int oldHashTableSize = *size;
    // New size of the growing by a factor of theree
    *size = (*size*3);
    struct Node** newHashTable = NULL;
    newHashTable = (struct Node**)calloc(*size,sizeof(struct Node*));
    if(!newHashTable){ fprintf(stderr,"Failed to allocate memory\n"); exit(1);}
    for (int i = 0; i < oldHashTableSize; i++) {
      if (hashTable[i] != NULL) {
          reHashWalk(newHashTable,hashTable[i],size);
    }
}
    cleanUpHashTable(hashTable,&oldHashTableSize,0);
    free(hashTable);
    return newHashTable;
  }


int reHashWalk (struct Node** newHashTable,struct Node* cursor, int *size) {
    if (cursor == NULL) {
      return 0;
    }
    // Rehash method here
    int newBucket = 0;
    newBucket = (crc64(cursor->combined) % *size);
    // If something is in the new hashTable bucket
    if(newHashTable[newBucket] != NULL) {
      struct Node* newHashTableCursor = newHashTable[newBucket];
      while (newHashTableCursor->next != NULL) {
          newHashTableCursor = newHashTableCursor->next;
      }
          // If there is something in the new Hashtable
          // We know the newHashTable[newBucket] == NULL
          struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));  // FREE THIS
          if(!node){fprintf(stderr,"Failed to allocate memory\n"); return 1;}
          node->combined = cursor->combined;
          node->freq = cursor->freq;
          newHashTableCursor->next = node;
    }
    // Nothing in the new Hashtable bucket
    else {
      struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));  // FREE THIS
      if(!node){fprintf(stderr,"Failed to allocate memory\n"); return 1;}
      node->combined = cursor->combined;
      node->freq = cursor->freq;
      newHashTable[newBucket] = node;
    }
        // Keep walking the old hashTable bucket
        if(cursor != NULL) {
          cursor = cursor->next;
          reHashWalk(newHashTable,cursor,size);
        }
        return 0;
}


int putAllStructsIntoArray(struct Node **hashTable,int *sizeTracker,int *size,struct Node **arrayOfStructs) {
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


struct Node** insertIntoHashTable(struct Node **hashTable,int *size,int *sizeTracker,struct Node *node, void *combined) { // Make this a void star
      char *combinedString = (char*)combined;
      int bucket = crc64(combinedString) % *size;
      int dupFlag = 0;
    if (hashTable[bucket] == NULL) {
        node->freq += 1;
        hashTable[bucket] = node;
        *sizeTracker += 1;
        return hashTable;
    }
        // There is something in the bucket
        struct Node* cursor = hashTable[bucket];
        // If there is nothing connected to the node->next property
        if((strcmp(cursor->combined,combinedString) == 0) && (cursor->next == NULL)) {
            cursor->freq += 1;
            dupFlag = 1;
        }
        else {
          while(cursor->next != NULL) {
            if(strcmp(cursor->combined,combinedString) == 0) {
                cursor->freq += 1;
                dupFlag = 1;
                break;
            }
              cursor = cursor->next;
          }
          // Cursor->next == NULL here
          // Catch the last node in the linked list
          if(cursor->next == NULL && strcmp(cursor->combined,combinedString) == 0) {
              cursor->freq += 1;
              dupFlag = 1;
          }
        }
        if(dupFlag) {
          dupFlag = 0;
          free(node->combined);
          free(node);
          return hashTable;
        }
        // Better be no duplicates here....
        node->freq += 1;
        cursor->next = node;
        *sizeTracker += 1;
        return hashTable;
}


struct Node** readWordPairs(FILE *fp, struct Node **hashTable,int *size,int *sizeTracker) {
      int wordOneFlag = 1;
      char *wordOne = getNextWord(fp);
      char *wordTwo = NULL;
      char *temp = NULL;
      while((wordTwo = getNextWord(fp))!= NULL) {
          if (*sizeTracker == (*size/2)) {
              hashTable = growHashTable(hashTable,size);
          }
          if (wordOneFlag) {
            int sizeOfStrings = strlen(wordOne) + strlen(wordTwo) + 2;
            void *combined = calloc(sizeOfStrings,sizeof(char));
            strcpy(combined,wordOne);
            strcat(combined," ");
            strcat(combined,wordTwo);
            struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
            if(!node){fprintf(stderr,"Failed to allocate memory\n");exit(0);}
            node->combined = combined; // More pointers to free
            hashTable = insertIntoHashTable(hashTable,size,sizeTracker,node,combined);
            wordOneFlag = 0;
            free(wordOne);
            temp = wordTwo;
          }
        else {
          wordOne = temp;
          int sizeOfStrings = strlen(wordOne) + strlen(wordTwo) + 2;
          void *combined = calloc(sizeOfStrings,sizeof(char));
          strcpy(combined,wordOne);
          strcat(combined," ");
          strcat(combined,wordTwo);
          struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
          if(!node){fprintf(stderr,"Failed to allocate memory\n");exit(0);}
          node->combined = combined; // More pointers to free
          hashTable = insertIntoHashTable(hashTable,size,sizeTracker,node,combined);
          free(temp);
          temp = wordTwo;
        }
    }
    free(temp);
    return hashTable;
}
