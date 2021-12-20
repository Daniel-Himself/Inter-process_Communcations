#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#define FIFO_WRITE_T "fifo_wt"
#define FIFO_READ_T "fifo_rt"
#define STR_LEN 100

void traslateToGerman(char *wordPtr);

int main(int argc, char *argv[])
{
  /*creat twofifos -if needed-*/
  char word[STR_LEN];
  FILE *descriptor_read;
  FILE *descriptor_write;

  /**
     * 0666 read only
 * 0644 write only */

  printf("******************");

  /*make fifo to read from student*/
  if (mknod(FIFO_READ_T, S_IFIFO | 0666, 0) == -1 && errno != EEXIST)
  {
    perror("cannot create fifo file");
    exit(EXIT_FAILURE);
  }

  /*read*/
  if (!(descriptor_read = fopen(FIFO_READ_T, "r")))
  {
    perror("cannot open fifo file for r");
    exit(EXIT_FAILURE);
  }

  /*make fifo to read from student`*/
  if (mknod(FIFO_WRITE_T, S_IFIFO | 0666, 0) == -1 && errno != EEXIST)
  {
    perror("cannot create fifo file");
    exit(EXIT_FAILURE);
  }
  /*write*/
  if (!(descriptor_write = fopen(FIFO_WRITE_T, "w")))
  {
    perror("cannot open fifo file for w");
    exit(EXIT_FAILURE);
  }

  /*wait for in-coming requests from student-s-*/
  while (fscanf(descriptor_read, " %s", word) != EOF && strcmp(word, "exit") != 0)
  {
    printf("******************");
    traslateToGerman(word);
    fprintf(descriptor_write, " %s\n", word);
    fflush(descriptor_write); // <== important
                              // read from fifo
  }
  fclose(descriptor_write);
  fclose(descriptor_read);
  unlink(FIFO_READ_T);
  unlink(FIFO_WRITE_T);
  /*create thread to read request*/

  // when getting exit:
  /*print bye*/

  /*join thrid*/
  //
}
void traslateToGerman(char *wordPtr)
{
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
    strcpy(wordPtr, "Unrecognized word, try again");
}