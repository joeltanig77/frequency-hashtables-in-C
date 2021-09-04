#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "hashTable.h"
#include "readWordPairs.h"
#include "sortHashTable.h"


struct Node** readWordPairs(FILE *fp, struct Node **hashTable, int *size,
  int *sizeTracker, int *memChecker) {
      int wordOneFlag = 1;
      char *wordOne = getNextWord(fp);
      char *wordTwo = NULL;
      char *temp = NULL;
      while((wordTwo = getNextWord(fp))!= NULL) {
          // Resize test,
          // if the items of the hashtable is half my hashtable size
          if (*sizeTracker == (*size/2)) {
              hashTable = growHashTable(hashTable,size,memChecker);
              if(!hashTable) {
                free(wordTwo);
                free(hashTable);
                free(temp);
                return NULL;
              }
          }
          if (wordOneFlag) {
            int sizeOfStrings = strlen(wordOne) + strlen(wordTwo) + 2;
            void *combined = (void*)calloc(sizeOfStrings,sizeof(char)); //DONE
            if (!combined) {
              *memChecker = 2;
              cleanUpHashTable(hashTable,size,1);
              free(wordOne);
              free(wordTwo);
              free(hashTable);
              free(temp);
              fprintf(stderr,"Failed to allocate memory\n");
              return NULL;
            }
            strcpy(combined,wordOne);
            strcat(combined," ");
            strcat(combined,wordTwo);
            hashTable = insertIntoHashTable(hashTable,size,sizeTracker,
              combined,memChecker);  //DONE
            if (!hashTable) {
              free(wordOne);
              free(wordTwo);
              free(hashTable);
              free(temp);
              free(combined);
              fprintf(stderr,"Failed to allocate memory\n");
              return NULL;
            }
            wordOneFlag = 0;
            free(wordOne);
            temp = wordTwo;
          }
        else {
          wordOne = temp;
          int sizeOfStrings = strlen(wordOne) + strlen(wordTwo) + 2;
          void *combined = (void*)calloc(sizeOfStrings,sizeof(char)); //DONE
          if (!combined) {
            *memChecker = 2;
            cleanUpHashTable(hashTable,size,1);
            free(wordTwo);
            free(hashTable);
            free(temp);
            fprintf(stderr,"Failed to allocate memory\n");
            return NULL;
          }
          strcpy(combined,wordOne);
          strcat(combined," ");
          strcat(combined,wordTwo);
          hashTable = insertIntoHashTable(hashTable,size,sizeTracker,
            combined,memChecker); //DONE
          if (!hashTable) {
            if(*memChecker != 4){
              *memChecker = 1;
            }
            free(wordTwo);
            free(hashTable);
            free(temp);
            free(combined);
            fprintf(stderr,"Failed to allocate memory\n");
            return NULL;
          }
          free(temp);
          temp = wordTwo;
        }
    }
    free(temp);
    return hashTable;
}
