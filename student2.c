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
	 FILE *descriptor1;
     // char str[] = "@campus.haifa.ac.il"; 
	 // errno == EEXIST if fifo already exists
	 if (mkfifo(FIFO_1, S_IFIFO | 0644) == -1 &&
		 errno != EEXIST) {
		 perror("cannot create fifo file") ;
		 exit(EXIT_FAILURE) ;
	 }

     // open fifo
	 if (!(descriptor1 = fopen(FIFO_1, "w"))) {
		 perror("cannot open fifo file for w") ;
		 exit(EXIT_FAILURE) ;
	 }

	 puts("Waiting for the server to start...\n");
	 while ( fgets(s, STR_LEN, stdin) != NULL) {
            fprintf(descriptor1, " %s\n", s) ;
		 fflush(descriptor1) ; // <== important
	 }
fclose(descriptor1);
unlink(FIFO_1);
 return EXIT_SUCCESS ;
} 