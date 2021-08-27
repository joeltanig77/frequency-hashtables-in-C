#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"
#include <ctype.h>

// atoi() turns a string into a integer

// 1 = there is a legal integer and 2 = not a legal integer
int isThereANumber(char argv[]) {
  int index = 0;
  while(argv[index] != '\0') {
    if(isdigit(argv[index])) {
      index++;
      continue;
    }
    // Not a digit
    return 2;
  }
  // We found a digit
  return 1;




}

int main(int argc, char *argv[]) {
   int linesToPrint = 0;
   int size = 200;
   struct Node** hashTable = NULL;
   hashTable = (struct Node**)calloc(size,sizeof(struct Node*));
   if (!hashTable){ fprintf(stderr,"Failed to allocate memory\n"); return 1;}

  int n = 1; // Arg counter that skips the pathway (pwd)
  if (isThereANumber(argv[1]) == 2) {
    printf("%s\n","Not a number");
    linesToPrint = -1; // Print Everything
  }
  else {
    n++; // Incrementing counter
    linesToPrint = atoi(argv[1]); // Turn string into a integer
    printf("The argument number is %d\n",linesToPrint);
  }
  while (n < argc) {
    FILE* fp = fopen(argv[n],"r");
    if(fp == NULL) {
      fprintf(stderr,"Can't open file\n");
      return 1;
    }
      n++;

      // Insert file pointer to insert to hashtable
      takeInPairs(fp,hashTable,&size);


      //char *c = getNextWord(fp);
      //printf("%s\n",c); //TODO: When I print this, then it leaks
      // The string is dynamic!!!!
      //  free(c);



      // Close file pointer
      fclose(fp);
  }


   cleanUpHashTable(hashTable,&size);

   free(hashTable);

  return 0;
}
