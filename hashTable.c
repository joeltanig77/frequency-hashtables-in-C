#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"


// Cursor assign temp to then free temp then continue walk.
int takeInPairs(FILE *fp, struct Node **hashTable,int size) {
    char wordOneStatic[100];
    char wordTwoStatic[100];
    char combined[100];
    int sizeTracker = 0;
    int bucket;
    char *wordOne = getNextWord(fp);
    strcpy(wordOneStatic,wordOne);
    strcpy(combined,wordOneStatic);
    free(wordOne);
    char *wordTwo = NULL;
    while((wordTwo = getNextWord(fp))!= NULL) {
        strcpy(wordTwoStatic,wordTwo);
        strcat(combined,wordTwoStatic);

        bucket = crc64(combined) % size;

      // If the hashTable is empty put in the node
      if (hashTable[bucket] == NULL) {
          struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
          node->wordOne = wordOneStatic;
          node->wordTwo = wordTwoStatic;
          node->combined = combined;

          hashTable[bucket] = node;

        //  hashTable[bucket].wordOne = wordOneStatic;
          printf("%s\n",hashTable[bucket]->wordOne);
        //  hashTable[bucket].wordTwo = wordTwoStatic;
          printf("%s\n",hashTable[bucket]->wordTwo);
        //  hashTable[bucket].combined = combined;
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

          while(cursor->next != NULL) {
              cursor = cursor->next;
          }


          struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
          node->wordOne = wordOneStatic;
          node->wordTwo = wordTwoStatic;
          node->combined = combined;

          cursor->next = node;  // TODO: Something breaks here

        //  hashTable[bucket].wordOne = wordOneStatic;
          printf("%s\n",cursor->wordOne);
        //  hashTable[bucket].wordTwo = wordTwoStatic;
          printf("%s\n",cursor->wordTwo);
        //  hashTable[bucket].combined = combined;
          printf("%s\n",cursor->combined);
          strcpy(wordOneStatic,wordTwoStatic);
          free(wordTwo);
          memset(combined,'\0',sizeof(char)*100);
          strcpy(wordOneStatic,wordTwoStatic);
          strcpy(combined,wordOneStatic);
          sizeTracker++;



      // // There is something is the hashTable, traverse the hashTable
      // for (int i=0; i < size; i++) {
      //     struct Node cursor;
      //     if (hashTable[i] == NULL) {
      //         continue;
      //   }
      //     // There is something in the bucket so recurse
      //      while(cursor != NULL) {
      //         cursor = hashTable[i]->next;
      //      }
      // }



}

  return 0;


}
