#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"

// Cursor assign temp to then free temp then continue walk.

// TODO 1:Need to do some UI stuff and fix the freq counting
// TODO 2: Keep working on Hashtables Expansion! Line 66 not assigning properly
//CHECK TO SEE IF THIS GROW Hashtableis ACTUALLY Growing



int cleanUpHashTable(struct Node **hashTable, int *size) {
    for (int i = 0; i < *size; i++) {
        if(hashTable[i] != NULL) {
          struct Node* cursor = hashTable[i];
          struct Node* temp = NULL;
          if(cursor->next == NULL) {
              free(cursor);
              continue;
          }
          while(cursor->next != NULL) {
              temp = cursor;
              cursor = cursor->next;
              free(temp);
          }
          free(cursor);
        }
    }
    return 0;
}


int compareFreq(const void *compare1,const void *compare2) {
    struct Node **node1 = (struct Node **)compare1;
    struct Node **node2 = (struct Node **)compare2;
    return (*node1)->freq - (*node2)->freq;
}



struct Node** growHashTable (struct Node** hashTable, int *size) {
    // Growing the hashTable by a factor of three
    int oldHashTableSize = *size;
    *size = (*size*3); // New size of the Hashtable
    struct Node** newHashTable = NULL;
    newHashTable = (struct Node**)calloc(*size,sizeof(struct Node*));
    if(!newHashTable){ fprintf(stderr,"Failed to allocate memory\n"); exit(1);}
    for (int i = 0; i < oldHashTableSize; i++) {
      if (hashTable[i] != NULL) {
          reHashWalk(newHashTable,hashTable[i],size);

    }
    // Need to make a walk function here that takes all the nodes in the
    // nodes and remaps them

    // Then finally reassign the old hashTable
    // Then free the other hashTable
    }

    cleanUpHashTable(hashTable,&oldHashTableSize); // Might have to assign this to something this has to be empty
    //hashTable = newHashTable;       ///////////////NOT SAVING THIS INSTANCE of the old hashTable
    //copyOldHashTableToNew(hashTable,newHashTable,size);
    // NEED TO COPY EVERYTHING AGAIN
	   free(hashTable);
    //cleanUpHashTable(newHashTable,size);
    //free(newHashTable);
    return newHashTable;
  }



int reHashWalk (struct Node** newHashTable,struct Node* cursor, int *size) {
    if (cursor == NULL) {
      return 0;
    }
    // rehash method here
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
          strcpy(node->wordOne,cursor->wordOne);
          strcpy(node->wordTwo,cursor->wordTwo);
          strcpy(node->combined,cursor->combined);
          node->freq = cursor->freq;
          // The newHashTable[newBucket]->next == NULL is so insert
          newHashTableCursor->next = node;              /////////// Something wrong with the cursor as it == NULL still
    }
    //Nothing in the new Hashtable bucket
    else {
      struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));  // FREE THIS
      if(!node){fprintf(stderr,"Failed to allocate memory\n"); return 1;}
      strcpy(node->wordOne,cursor->wordOne);
      strcpy(node->wordTwo,cursor->wordTwo);
      strcpy(node->combined,cursor->combined);
      node->freq = cursor->freq;
      newHashTable[newBucket] = node;
    }


        // newHashTableCursor = cursor;
        // Keep walking the old hashTable bucket
        if(cursor != NULL) {
          cursor = cursor->next;
          reHashWalk(newHashTable,cursor,size);
        }
        return 0;
}



int putAllStuctsIntoArray(struct Node **hashTable,int *sizeTracker,int *size,struct Node *arrayOfStructs[]) {
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
            // array of structs should be empty here
            arrayOfStructs[j] = hashTable[i];
            continue;
        }
        while(cursor->next != NULL) {
          while(arrayOfStructs[j] != NULL) {
            j++;
          }
            // array of structs should be empty here
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



int takeInPairs(FILE *fp, struct Node **hashTable,int *size,int *sizeTracker) { // Make this a void star
      char wordOneStatic[256];
      char wordTwoStatic[256];
      char combined[512];
      int dubFlag = 0;
      int bucket;
      char *wordOne = getNextWord(fp);
      strcpy(wordOneStatic,wordOne);
      strcpy(combined,wordOneStatic);
      free(wordOne);
      char *wordTwo = NULL;
      while((wordTwo = getNextWord(fp))!= NULL) {
          ///////////////////////////////////// TODO: START HERE
          // if (*sizeTracker == (*size/2)) {
          //   //  struct Node **hashTable;
          //     hashTable = growHashTable(hashTable,size);
          // }

          strcpy(wordTwoStatic,wordTwo);
          strcat(combined,wordTwoStatic);

          bucket = crc64(combined) % *size;
            printf("%s\n",wordOne);
          //  printf("%s\n",wordTwo);
            printf("%s\n",combined);
        // If the hashTable is empty put in the node
        if (hashTable[bucket] == NULL) {
            struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
            if(!node){fprintf(stderr,"Failed to allocate memory\n"); return 1;}
            strcpy(node->wordOne, wordOneStatic);
            strcpy(node->wordTwo, wordTwoStatic);
            strcpy(node->combined, combined);
            node->freq += 1;

            hashTable[bucket] = node;


          //  printf("%s\n",hashTable[bucket]->wordOne);
          //  printf("%s\n",hashTable[bucket]->wordTwo);
            //printf("%s\n",hashTable[bucket]->combined);
            strcpy(wordOneStatic,wordTwoStatic);
            free(wordTwo);
            memset(combined,'\0',sizeof(char)*100);
            strcpy(wordOneStatic,wordTwoStatic);
            strcpy(combined,wordOneStatic);
            *sizeTracker += 1;
            continue;
        }


            // There is something in the bucket
            struct Node* cursor = hashTable[bucket];

            if(strcmp(cursor->combined,combined) == 0) {
                cursor->freq += 1; /////////////////////////ONE OFF ERROR
                printf("%s\n",cursor->combined);
                printf("%d\n",cursor->freq);
                dubFlag = 1;
            }
            while(cursor->next != NULL) {
              if(strcmp(cursor->combined,combined) == 0) {
                  cursor->freq += 1; /////////////////////////ONE OFF ERROR
                  dubFlag = 1;
                  break;
              }
                cursor = cursor->next;
            }

            if(strcmp(cursor->combined,combined) == 0) {
                cursor->freq += 1; /////////////////////////ONE OFF ERROR
                dubFlag = 1;

            }

            if (dubFlag) {
              strcpy(wordOneStatic,wordTwoStatic);
              free(wordTwo);
              memset(combined,'\0',sizeof(char)*100);
              strcpy(wordOneStatic,wordTwoStatic);
              strcpy(combined,wordOneStatic);
              dubFlag = 0;
              continue;
            }
            // Better be no duplicates here....

            struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
            if(!node){fprintf(stderr,"Failed to allocate memory\n"); return 1;}
            strcpy(node->wordOne, wordOneStatic);
            strcpy(node->wordTwo, wordTwoStatic);
            strcpy(node->combined, combined);
            node->freq += 1;
            cursor->next = node;
          //  printf("%s\n",cursor->wordOne);
          //  printf("%s\n",cursor->wordTwo);
          //  printf("%s\n",cursor->combined);
            strcpy(wordOneStatic,wordTwoStatic);
            free(wordTwo);
            memset(combined,'\0',sizeof(char)*100);
            strcpy(wordOneStatic,wordTwoStatic);
            strcpy(combined,wordOneStatic);
            *sizeTracker += 1;
    }
    return 0;

}
