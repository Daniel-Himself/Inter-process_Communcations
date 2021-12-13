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
	 FILE *fdr;
      char str[] = "@campus.haifa.ac.il"; 
	 if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1 &&
		 errno != EEXIST) {
		 perror("cannot create fifo file") ;
		 exit(EXIT_FAILURE) ;
	 }

	 if (!(fdr = fopen(FIFO_NAME, "r"))) {
		 perror("cannot open fifo file for r") ;
		 exit(EXIT_FAILURE) ;
	 }

	 printf("Server ready, waiting for the client\n");
	 while ( fscanf(fdr, " %s", s) != EOF && strcmp(s,"exit")!=0){
            int k = strlen(s); 
            int i; 
            for (i=0; i<strlen(str); i++) 
                s[k++] = str[i];
            s[k] = '\0';    

	 	printf("Got: %s\n", s) ;
}
fclose(fdr);
unlink(FIFO_NAME);
	 return EXIT_SUCCESS ;
} 