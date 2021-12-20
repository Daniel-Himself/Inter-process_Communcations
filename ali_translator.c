#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h> // thread functionality
#define FIFO_WT "fifo_wt"
#define FIFO_RT "fifo_rt"
#define STR_LEN 100

void* translateToGerman(void * args);

  /*creat twofifos -if needed-*/
  char word[STR_LEN];
  FILE *fdr;
  FILE *fdw;

int main(int argc, char *argv[])
{
  pthread_t thread_data;
  int status;


  /*make fifo to read from student*/
  if (mkfifo(FIFO_RT, 0777 | O_RDONLY) == -1 && errno != EEXIST)
  {
    perror("cannot create fifo file");
    exit(EXIT_FAILURE);
  }

  /*read*/
  if (!(fdr = fopen(FIFO_RT, "r")))
  {
    perror("cannot open fifo file for r");
    exit(EXIT_FAILURE);
  }

  /*make fifo to read from student`*/
  if (mkfifo(FIFO_WT, S_IFIFO | 0777) == -1 && errno != EEXIST)
  {
    perror("cannot create fifo file");
    exit(EXIT_FAILURE);
  }
  /*write*/
  if (!(fdw = fopen(FIFO_WT, "w")))
  {
    perror("cannot open fifo file for w");
    exit(EXIT_FAILURE);
  }

  /*wait for in-coming requests from student-s-*/
  while (fscanf(fdr, " %s", word) != EOF)
  {
    status = pthread_create(&thread_data, NULL, translateToGerman, (void *)&word); // create thread
    if (status != 0)
    {
      fputs("pthread_create failed in main", stderr);
      exit(EXIT_FAILURE);
    }
    //ranslateToGerman(word); for a version without threads
    // fprintf(fdw, " %s\n", word);
    // fflush(fdw); // <== important
    // // read from fifo
  }

  fclose(fdw);
  fclose(fdr);
  unlink(FIFO_RT);
  unlink(FIFO_WT);
  return EXIT_SUCCESS;
  /*create thread to read request*/

  // when getting exit:
  /*print bye*/

  /*join thrid*/
  //
}

void* translateToGerman(void * args)
{
  char* wordPtr = (char*) args;

  //printf("%s\n", wordPtr); //test

  char *word1 = {"hallo"};
  char *word2 = {"Schmetterling"};
  char *word3 = {"danke"};
  char *word4 = {"kuchen"};
  char *word5 = {"Bye"};
  char *word6 = {"krankenwagen"};

  if (strcmp(wordPtr, "hello") == 0)
  {
    strcpy(wordPtr, word1);
  }
  else if (strcmp(wordPtr, "butterfly") == 0)
  {
    strcpy(wordPtr, word2);
  }
  else if (strcmp(wordPtr, "thanks") == 0)
  {
    strcpy(wordPtr, word3);
  }
  else if (strcmp(wordPtr, "cake") == 0)
  {
    strcpy(wordPtr, word4);
  }
  else if (strcmp(wordPtr, "exit") == 0)
  {
    strcpy(wordPtr, word5);
  }
  else if (strcmp(wordPtr, "ambulance") == 0)
  {
    strcpy(wordPtr, word6);
  }
  else
    strcpy(wordPtr, "Unrecognized");

  //printf("%s\n", wordPtr); //test

  fprintf(fdw, " %s\n", word);
  fflush(fdw); // <== important
  // read from fifo
}