#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "crc64.h"



int main(int argc, char *argv[]) {
  int n = 1;
  while (n < argc) {
    FILE* fp = fopen(argv[n],"r");
    if(fp == NULL) {
      fprintf(stderr,"Can't open file\n");
      return 1;
    }
      n++;

      printf("%s\n",getNextWord(fp));
      fclose(fp);
  }



  // Iterate n here




  return 0;
}
