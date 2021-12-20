#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>      // thread functionality
#define FIFO_WT "fifo_wt" // the fifo that the translator writes to
#define FIFO_RT "fifo_rt" // the fifo that the translator reads from
#define STR_LEN 100

void *translateToGerman(void *args);

/*creat twofifos -if needed-*/
FILE *fdr; // descriptor for reading from the student
FILE *fdw; // descriptor for writing back to the student

int main(int argc, char *argv[])
{
  char word[STR_LEN];    // word to be translated
  pthread_t thread_data; // declaration of a thread to be used later
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
    printf("Got: %s\n", word);
    status = pthread_create(&thread_data, NULL, translateToGerman, (void *)&word); // create thread
    if (status != 0)
    {
      fputs("pthread_create failed in main", stderr);
      exit(EXIT_FAILURE);
    }
  }
  printf("Translator shut down.\n");

  fclose(fdw);
  fclose(fdr);
  unlink(FIFO_RT);
  unlink(FIFO_WT);
  return EXIT_SUCCESS;
}

void *translateToGerman(void *args)
{
  char *wordPtr = (char *)args;

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

  // send the translated word back to the student
  fprintf(fdw, " %s\n", wordPtr);
  fflush(fdw); // <== important

  printf("Translation sent...\n");
}