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
   int size = 25;
   int sizeTracker = 0;
   struct Node** arrayOfStructs = NULL;
   struct Node** hashTable = NULL;
   hashTable = (struct Node**)calloc(size,sizeof(struct Node*));
   if (!hashTable){ fprintf(stderr,"Failed to allocate memory\n"); exit(1);}


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
      takeInPairs(fp,hashTable,&size,&sizeTracker);

      arrayOfStructs = (struct Node**)calloc(sizeTracker,sizeof(struct Node*));
      if (!arrayOfStructs){ fprintf(stderr,"Failed to allocate memory\n"); exit(1);}

      putAllStuctsIntoArray(hashTable,&sizeTracker,&size,arrayOfStructs);


      // Close file pointer
      fclose(fp);
  }

   free(arrayOfStructs);
   cleanUpHashTable(hashTable,&size); //TURN THIS OFF WHEN I DO RESIZE!
   free(hashTable);                   //TURN THIS OFF WHEN I DO RESIZE!

  return 0;
}
