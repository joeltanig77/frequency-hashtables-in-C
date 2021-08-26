#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"

int takeInPairs(FILE *fp, struct Node *hashTable,int size) {
    int sizeTracker = 0;
    int bucket;
    char wordOneStatic[100];
    char *wordOne;
    char *wordTwo;
    while(getNextWord(fp)!= NULL) {
        char wordTwoStatic[100];
        wordOne = getNextWord(fp);
        wordTwo = getNextWord(fp);
        strcpy(wordOneStatic,wordOne);
        strcpy(wordTwoStatic,wordTwo);
        printf("%s\n",wordOne);
        printf("%s\n",wordTwo);
        // Hash the words combine
        strcat(wordOne,wordTwo);
        // Hash the words
        bucket = crc64(wordOne) % size;
        printf("%d\n",bucket);
        // Need to figure out why -> is not used... and that its only inserting the concat...
        hashTable[bucket].wordOne = wordOneStatic;
        hashTable[bucket].wordTwo = wordTwoStatic;
        hashTable[bucket].combined = wordOne;
        free(wordOne);
        free(wordTwo);
        sizeTracker++;

        // TODO: Need to do the proper wordTwo = wordOne logic here!!!!!
}

  return 0;


}
