#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"

// Cursor assign temp to then free temp then continue walk.

// TODO: Expand the hashTable next
// TODO: Fix one off freq counter


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
    *size = (*size *3);
    int bucket;
    struct Node** newHashTable = NULL;
    newHashTable = (struct Node**)calloc(*size,sizeof(struct Node*));
    if(!newHashTable){ fprintf(stderr,"Failed to allocate memory\n"); return 1;}
    for (int i = 0; i < *size; i++) {
      if (hashTable[i] != NULL) {
          struct Node* cursor = hashTable[i];
          // Need to save the node here
          if(cursor->next == NULL) {
              bucket = (crc64(cursor->combined) % *size);
              newHashTable[bucket] = cursor;
              continue;
          }
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
    return 0;
  }


int takeInPairs(FILE *fp, struct Node **hashTable,int *size) {
    char wordOneStatic[100];
    char wordTwoStatic[100];
    char combined[100];
    int sizeTracker = 0;
    int dubFlag = 0;
    int bucket;
    char *wordOne = getNextWord(fp);
    strcpy(wordOneStatic,wordOne);
    strcpy(combined,wordOneStatic);
    free(wordOne);
    char *wordTwo = NULL;
    while((wordTwo = getNextWord(fp))!= NULL) {
        // if (sizeTracker == (*size/2)) {
        //     growHashTable(hashTable,size);
        // }

        strcpy(wordTwoStatic,wordTwo);
        strcat(combined,wordTwoStatic);

        bucket = crc64(combined) % *size;

      // If the hashTable is empty put in the node
      if (hashTable[bucket] == NULL) {
          struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
          if(!node){fprintf(stderr,"Failed to allocate memory\n"); return 1;}
          strcpy(node->wordOne, wordOneStatic);
          // node->wordOne = wordOneStatic;
          // node->wordTwo = wordTwoStatic;
          strcpy(node->wordTwo, wordTwoStatic);
          // node->combined = combined;
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
          if (dubFlag) {
            strcpy(wordOneStatic,wordTwoStatic);
            free(wordTwo);
            memset(combined,'\0',sizeof(char)*100);
            strcpy(wordOneStatic,wordTwoStatic);
            strcpy(combined,wordOneStatic);
            sizeTracker++;
            dubFlag = 0;
            continue;
          }
           //We can a duplicate, go back up
          // Better be no duplicates here....

          struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
          if(!node){fprintf(stderr,"Failed to allocate memory\n"); return 1;}
          // node->wordOne = wordOneStatic;
          // node->wordTwo = wordTwoStatic;
          // node->combined = combined;
          strcpy(node->wordOne, wordOneStatic);
          strcpy(node->wordTwo, wordTwoStatic);
          strcpy(node->combined, combined);
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
