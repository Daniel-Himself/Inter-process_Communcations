#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_1 "a_fifo"
#define STR_LEN 100
int main()
{
	 char s[STR_LEN];
	 FILE *descriptor2;
      char str[] = "@campus.haifa.ac.il"; 
	 if (mknod(FIFO_1, S_IFIFO | 0666, 0) == -1 &&
		 errno != EEXIST) {
		 perror("cannot create fifo file") ;
		 exit(EXIT_FAILURE) ;
	 }

	 if (!(descriptor2 = fopen(FIFO_1, "r"))) {
		 perror("cannot open fifo file for r") ;
		 exit(EXIT_FAILURE) ;
	 }

	 printf("Server ready, waiting for the client\n");
	 while (fscanf(descriptor2, " %s", s) != EOF && strcmp(s, "exit") != 0)
	 {
		 int k = strlen(s);
		 int i;
		//  for (i = 0; i < strlen(str); i++)
		// 	 s[k++] = str[i];
		 s[k] = '\0';

		 printf("Got: %s\n", s);
	 }
fclose(descriptor2);
unlink(FIFO_1);
	 return EXIT_SUCCESS ;
} 