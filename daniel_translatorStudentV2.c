#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#define STR_LEN 100

/*Methods*/
void traslateToGerman(char *wordPtr);

/*end*/

int main(int argc, char *argv[])
{
  int fd1[2]; // stores two ends of first pipe parent
  int fd2[2]; // stores two ends of second pipe son
  // char word[STR_LEN];

  pid_t status;

  /*fork proccesses to student and translator (parent - son)*/
  while (1)
  {

    /*create both pipes*/
    if (pipe(fd1) == -1)
    {
      fprintf(stderr, "Pipe 1 Failed");
      return 1;
    }
    if (pipe(fd2) == -1)
    {
      fprintf(stderr, "Pipe 2 Failed");
      return 1;
    }

    status = fork();
    if (status < 0)
    {
      fprintf(stderr, "fork Failed");
      return 1;
    }

    // Parent process (student)
    else if (status > 0)
    {
      char word[100];

      printf("Enter English Word: ");
      if (!scanf("%s", word))
      {
        printf("Input Error!");
        exit(EXIT_FAILURE);
      }

      close(fd1[0]); // close reading in pipe
      write(fd1[1], word, strlen(word) + 1);
      close(fd1[1]);

      // Wait for child to send the translation
      wait(&status);
      close(fd2[1]);
      read(fd2[0], word, 100);
      close(fd2[0]);
      printf("The word in German: %s\n", word);
      if (strcmp(word, "Bye") == 0)
      {
        exit(EXIT_SUCCESS);
      }
    }

    // child process (translator)
    else
    {
      char toSend[STR_LEN];
      close(fd1[1]);
      read(fd1[0], toSend, STR_LEN);
      traslateToGerman(toSend);
      close(fd1[0]);
      close(fd2[0]);
      write(fd2[1], toSend, strlen(toSend) + 1);
      close(fd2[1]);
      exit(EXIT_SUCCESS);
    }
  }
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