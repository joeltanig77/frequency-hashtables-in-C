#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"
#include "hashTable.h"
#include <ctype.h>

// atoi() turns a string into a integer

// 1 = there is a legal integer and 2 = not a legal integer 3 = no - seen 4 = illeal line arg.
int isThereANumber(char argv[]) {
  int index = 0;
  // If - and not a digit eg. -e
  if((argv[0] == 45) && (!(isdigit(argv[1])))) {
    return 2;
  }

  if(argv[0] != 45) {
    return 4;
  }
  // Skip the - sign
  index++;
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
    if (argc == 1) {
      fprintf(stderr,"Error: no fileName arguments specified.\n\n");
      fprintf(stderr,"\tUsage: ./wordpairs <-count> fileName1 <fileName2> ...\n\n");
      fprintf(stderr,"\tWhere: count is the number of words to display\n\n");
      exit(0);
    }
   int linesToPrint = 0;
   int size = 1;
   int sizeTracker = 0;
   struct Node** arrayOfStructs = NULL;
   struct Node** hashTable = NULL;
   hashTable = (struct Node**)calloc(size,sizeof(struct Node*));
   if (!hashTable){ fprintf(stderr,"Failed to allocate memory\n"); exit(1);}
  int n = 1; // Arg counter that skips the pathway (pwd)
  FILE* fp2 = fopen(argv[n],"r");
  if(fp2 != NULL) {
    linesToPrint = -1;
    fclose(fp2);
  }
  // Have a line arg
  else if (isThereANumber(argv[1]) == 4){
    fprintf(stderr,"Must assign - to count argument\n\n");
    fprintf(stderr,"\tUsage ./wordpairs <-count> fileName1 <fileName2> ...\n\n");
    fprintf(stderr,"\tWhere: count is the number of words to display\n\n");
    free(hashTable);
    exit(0);
  }
  else if (isThereANumber(argv[1]) == 2) {
    fprintf(stderr,"Not a legal count argument\n\n");
    fprintf(stderr,"\tUsage ./wordpairs <-count> fileName1 <fileName2> ...\n\n");
    fprintf(stderr,"\tWhere: count is the number of words to display\n\n");
    free(hashTable);
    exit(0);
  }
  else {
    n++; // Incrementing counter
    linesToPrint = atoi(argv[1])*-1; // Turn string into a integer
  }
  while (n < argc) {
    FILE* fp = fopen(argv[n],"r");
    if(fp == NULL) {
      free(hashTable);
      fprintf(stderr,"Can't open file\n");
      exit(0);
    }
      n++;

      // Insert file pointer to insert to hashtable
      hashTable = readWordPairs(fp,hashTable,&size,&sizeTracker);

      // Close file pointer
      fclose(fp);
  }
    arrayOfStructs = (struct Node**)calloc(sizeTracker,sizeof(struct Node*));
    if (!arrayOfStructs){
       fprintf(stderr,"Failed to allocate memory\n");
       cleanUpHashTable(hashTable,&size,1); //TURN THIS OFF WHEN I DO RESIZE!
       free(hashTable);
       exit(1);
     }

    putAllStructsIntoArray(hashTable,&sizeTracker,&size,arrayOfStructs);

    qsort(arrayOfStructs,sizeTracker,sizeof(struct Node*),compareFreq);

    if(linesToPrint == -1) {
      for(int i=0; i < sizeTracker; i++) {
          printf("%10d",arrayOfStructs[i]->freq);
          printf(" %s\n",(char*)arrayOfStructs[i]->combined);
      }
    }
    else {
      for(int i=0; i < linesToPrint; i++) {
          printf("%10d",arrayOfStructs[i]->freq);
          printf(" %s\n",(char*)arrayOfStructs[i]->combined);
      }
    }

   // Freeing before exit
   free(arrayOfStructs);
   cleanUpHashTable(hashTable,&size,1);
   free(hashTable);

  return 0;
}
