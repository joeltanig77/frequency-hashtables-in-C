#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"

// Cursor assign temp to then free temp then continue walk.

// TODO 1: Keep working on Hashtables Expansion! Line 110 not assigning properly
// TODO: Fix one off freq counter (maybe)
// TODO 3: Put everything into an Array and use Qsort so walk the hashTable and
// put everything into an array.


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

int growHashTable (struct Node** hashTable, int *size) {
    // Growing the hashTable by a factor of three
    *size = (*size*2);
    struct Node** newHashTable = NULL;
    newHashTable = (struct Node**)calloc(*size,sizeof(struct Node*));
    if(!newHashTable){ fprintf(stderr,"Failed to allocate memory\n"); exit(1);}
    for (int i = 0; i < *size; i++) {
      if (hashTable[i] != NULL) {
          reHashWalk(newHashTable,hashTable[i],size);




          // while(cursor->next != NULL) {
          //     temp = cursor;
          //     cursor = cursor->next;
          //     free(temp);
          // }

    }
    // Need to make a walk function here that takes all the nodes in the
    // nodes and remaps them

    // Then finally reassign the old hashTable
    // Then free the other hashTable
    }
    cleanUpHashTable(hashTable,size);
    hashTable = newHashTable;
    return 0;
  }



int reHashWalk (struct Node** newHashTable,struct Node* cursor, int *size) {
    if (cursor == NULL) {
      return 0;
    }
    // rehash method here
    int newBucket = 0;
    // Something is in the new hashTable bucket
    newBucket = (crc64(cursor->combined) % *size);
    if(newHashTable[newBucket] != NULL) {
      struct Node* newHashTableCursor = newHashTable[newBucket];
      while (newHashTableCursor->next != NULL) { /////////// Something wrong with the cursor
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



int takeInPairs(FILE *fp, struct Node **hashTable,int *size) {
      char wordOneStatic[256];
      char wordTwoStatic[256];
      char combined[512];
      int sizeTracker = 0;
      int dubFlag = 0;
      int bucket;
      char *wordOne = getNextWord(fp);
      strcpy(wordOneStatic,wordOne);
      strcpy(combined,wordOneStatic);
      free(wordOne);
      char *wordTwo = NULL;
      while((wordTwo = getNextWord(fp))!= NULL) {
          ///////////////////////////////////// TODO: START HERE
          if (sizeTracker == (*size/2)) {
              growHashTable(hashTable,size);
          }

          strcpy(wordTwoStatic,wordTwo);
          strcat(combined,wordTwoStatic);

          bucket = crc64(combined) % *size;

        // If the hashTable is empty put in the node
        if (hashTable[bucket] == NULL) {
            struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
            if(!node){fprintf(stderr,"Failed to allocate memory\n"); return 1;}
            strcpy(node->wordOne, wordOneStatic);
            strcpy(node->wordTwo, wordTwoStatic);
            strcpy(node->combined, combined);
            node->freq += 1;

            hashTable[bucket] = node;


            printf("%s\n",hashTable[bucket]->wordOne);
            printf("%s\n",hashTable[bucket]->wordTwo);
            printf("%s\n",hashTable[bucket]->combined);
            strcpy(wordOneStatic,wordTwoStatic);
            free(wordTwo);
            memset(combined,'\0',sizeof(char)*100);
            strcpy(wordOneStatic,wordTwoStatic);
            strcpy(combined,wordOneStatic);
            sizeTracker++;
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
            printf("%s\n",cursor->wordOne);
            printf("%s\n",cursor->wordTwo);
            printf("%s\n",cursor->combined);
            strcpy(wordOneStatic,wordTwoStatic);
            free(wordTwo);
            memset(combined,'\0',sizeof(char)*100);
            strcpy(wordOneStatic,wordTwoStatic);
            strcpy(combined,wordOneStatic);
            sizeTracker++;
    }
    return 0;

}
