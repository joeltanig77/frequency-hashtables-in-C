#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"
#include <ctype.h>

// atoi() turns a string into a integer

// 1 = there is a number and 2 = there is no number 3 = not a text file
int isThereANumber(char argv[]) {
  int index = 0;
  while(argv[index] != '\0') {
    if(isdigit(argv[index])) {
      index++;
      continue;
    }
    // Not a digit there
    return 2;
  }
  return 1;




}

int main(int argc, char *argv[]) {
   int linesToPrint = 0;

   int size = 500;
   struct Node* hashTable = NULL;
   hashTable = (struct Node*)calloc(size,sizeof(struct Node));
   if (hashTable == NULL) return 1;

  int n = 1; // Arg counter that skips the pathway
  if (isThereANumber(argv[1]) == 2) {
    fprintf(stderr,"Not a number\n");
  }
  else {
    n++; // Incrementing counter
    linesToPrint = atoi(argv[1]); // Turn string into the array
    printf("The argument number is %d\n",linesToPrint);
  }
  while (n < argc) {
    printf("%d\n",argc);
    FILE* fp = fopen(argv[n],"r");
    if(fp == NULL) {
      fprintf(stderr,"Can't open file\n");
      return 1;
    }
      n++;


      takeInPairs(fp,hashTable,size);



      //char *c = getNextWord(fp);

      //printf("%s\n",c); //TODO: When I print this, then it leaks

      // The string is dynamic!!!!
      //  free(c);
      // free(hashTable); //This is broken

      fclose(fp);
  }





  return 0;
}
