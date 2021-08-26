#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"

int takeInPairs(FILE *fp, struct Node *hashTable,int size) {
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




        hashTable[bucket].wordOne = wordOneStatic;
        printf("%s\n",hashTable[bucket].wordOne);
        hashTable[bucket].wordTwo = wordTwoStatic;
        printf("%s\n",hashTable[bucket].wordTwo);
        hashTable[bucket].combined = combined;
        printf("%s\n",hashTable[bucket].combined);
        strcpy(wordOneStatic,wordTwoStatic);
        free(wordTwo);
        memset(combined,'\0',sizeof(char)*100);
        strcpy(wordOneStatic,wordTwoStatic);
        strcpy(combined,wordOneStatic);
        sizeTracker++;
}

  return 0;


}
