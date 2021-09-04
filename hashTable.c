#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"


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




struct Node** growHashTable (struct Node** hashTable, int *size, int *memChecker) {
    // Growing the hashTable by a factor of three
    int oldHashTableSize = *size;
    // New size of the growing by a factor of three
    *size = (*size*3);
    struct Node** newHashTable = NULL;
    newHashTable = (struct Node**)calloc(*size,sizeof(struct Node*));  //DONE
    if(!newHashTable){
      *memChecker = 3;
      cleanUpHashTable(hashTable,&oldHashTableSize,1);
      fprintf(stderr,"Failed to allocate memory\n");
      return NULL;
    }
    for (int i = 0; i < oldHashTableSize; i++) {
      if (hashTable[i] != NULL) {
          int checkMem = reHashWalk(newHashTable,hashTable[i],size); //DONE
          if (checkMem == -1) {
            *memChecker = 3;
            cleanUpHashTable(hashTable,&oldHashTableSize,1);
            free(hashTable);
            free(newHashTable);
            fprintf(stderr,"Failed to allocate memory\n");
            return NULL;
          }
    }
}
    cleanUpHashTable(hashTable,&oldHashTableSize,0);
    free(hashTable);
    return newHashTable;
  }


int reHashWalk (struct Node** newHashTable,struct Node* cursor, int *size) {
    int memCheck = 0;
    if (cursor == NULL) {
      return 0;
    }
    // Rehash method here
    int newBucket = 0;
    newBucket = (crc64((char*)cursor->combined) % *size);
    // If something is in the new hashTable bucket
    if(newHashTable[newBucket] != NULL) {
      struct Node* newHashTableCursor = newHashTable[newBucket];
      while (newHashTableCursor->next != NULL) {
          newHashTableCursor = newHashTableCursor->next;
      }
          // If there is something in the new Hashtable
          // We know the newHashTable[newBucket] == NULL
          struct Node* node = (struct Node*)calloc(1,sizeof(struct Node)); //DONE
          if(!node) {
            cleanUpHashTable(newHashTable,size,0);
            return -1;
          }
          node->combined = cursor->combined;
          node->freq = cursor->freq;
          newHashTableCursor->next = node;
    }
    // Nothing in the new Hashtable bucket
    else {
      struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));   //DONE
      if(!node) {
        cleanUpHashTable(newHashTable,size,0);
        return -1;
      }
      node->combined = cursor->combined;
      node->freq = cursor->freq;
      newHashTable[newBucket] = node;
    }
        // Keep walking the old hashTable bucket
        if(cursor != NULL) {
          cursor = cursor->next;
          memCheck = reHashWalk(newHashTable,cursor,size);
        }
        if(memCheck == -1){
          return -1;
        }
        return 0;
}



struct Node** insertIntoHashTable(struct Node **hashTable,int *size,
  int *sizeTracker, void *combined, int *memChecker) {
      int bucket = crc64((char*)combined) % *size;
      int dupFlag = 0;
    if (hashTable[bucket] == NULL) {
      struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));  //DONE
      if(!node) {
        return NULL;
      }
        node->freq += 1;
        hashTable[bucket] = node;
        node->combined = combined; // More pointers to free
        *sizeTracker += 1;
        return hashTable;
    }
        // There is something in the bucket
        struct Node* cursor = hashTable[bucket];
        // If there is nothing connected to the node->next property
        if((strcmp((char*)cursor->combined,(char*)combined) == 0)
        && (cursor->next == NULL)) {
            cursor->freq += 1;
            dupFlag = 1;
        }
        else {
          while(cursor->next != NULL) {
            if(strcmp((char*)cursor->combined,(char*)combined) == 0) {
                cursor->freq += 1;
                dupFlag = 1;
                break;
            }
              cursor = cursor->next;
          }
          // Cursor->next == NULL here
          // Catch the last node in the linked list
          if(cursor->next == NULL &&
            strcmp((char*)cursor->combined,(char*)combined) == 0) {
              cursor->freq += 1;
              dupFlag = 1;
          }
        }
        if(dupFlag) {
          free(combined);
          dupFlag = 0;
          return hashTable;
        }
        // Better be no duplicates here....
        struct Node* node = (struct Node*)calloc(1,sizeof(struct Node)); //DONE
        if(!node) {
          *memChecker = 4;
          cleanUpHashTable(hashTable,size,1);
          free(hashTable);
          return NULL;
        }
        node->freq += 1;
        cursor->next = node;
        node->combined = combined; // More pointers to free
        *sizeTracker += 1;
        return hashTable;
}
