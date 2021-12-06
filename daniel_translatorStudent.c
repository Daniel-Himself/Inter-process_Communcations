#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // for wait()
#include <stdlib.h>

int main() {
  int my_pipe[2];
  int status;
  char father_buff[6];
  int index = 0;

  status = pipe(my_pipe);
  if (status == -1) {
    printf("Unable to open pipe\n");
    exit(-1);
  }

  status = fork();
  if (status == -1) {
    printf("Unable to fork\n");
    exit(-1);
  }
  if (status == 0) {     /* (translator) son process */
     close(my_pipe[0]);
      write(my_pipe[1], "Hello", 6 * sizeof(char));
      exit(0);
    }
    else {    /* (student) father process */

      wait(&status);    /* wait until son process finishes */
     close(my_pipe[1]);
      read(my_pipe[0], father_buff, 6);
      printf("Got from pipe: %s\n", father_buff);
      exit(0);
    }
}
 

  
