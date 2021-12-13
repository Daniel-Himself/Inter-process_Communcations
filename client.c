#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "a_fifo"
#define STR_LEN 100

int main()
{
	 char s[STR_LEN];
	 FILE *fdw;
      char str[] = "@campus.haifa.ac.il"; 
	 // errno == EEXIST if fifo already exists
	 if (mkfifo(FIFO_NAME, S_IFIFO | 0644) == -1 &&
		 errno != EEXIST) {
		 perror("cannot create fifo file") ;
		 exit(EXIT_FAILURE) ;
	 }
	 if (!(fdw = fopen(FIFO_NAME, "w"))) {
		 perror("cannot open fifo file for w") ;
		 exit(EXIT_FAILURE) ;
	 }
	 puts("Waiting for the server to start...\n");
	 while ( fgets(s, STR_LEN, stdin) != NULL) {
            fprintf(fdw, " %s\n", s) ;
		 fflush(fdw) ; // <== important
	 }
fclose(fdw);
unlink(FIFO_NAME);
 return EXIT_SUCCESS ;
} 