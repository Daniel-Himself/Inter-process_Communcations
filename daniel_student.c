#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#define FIFO_WT "fifo_wt"
#define FIFO_RT "fifo_rt"
#define STR_LEN 100

int main(int argc, char *argv[])
{
    /*might need this*/
    // char *cptr = NULL, exitstr = {"exit"};
    /* 1. open reader and writer fifo recpectively*/
    char word[STR_LEN];
    FILE *fdw;
    FILE *fdr;

    /*write*/
    if (!(fdr = fopen(FIFO_RT, "w")))
    {
        perror("cannot open fifo file for w");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(FIFO_WT, 0666 | O_RDONLY) == -1 && errno != EEXIST)
    {
        perror("cannot create fifo file");
        exit(EXIT_FAILURE);
    }

    /*read*/
    if (!(fdw = fopen(FIFO_WT, "r")))
    {
        perror("cannot open fifo file for r");
        exit(EXIT_FAILURE);
    }

    /* 2. recive strings from user until receiving "exit" */
    while (1)
    {
        printf("Enter English Word: ");
        if (fgets(word, STR_LEN, stdin) != NULL)
        {
            fprintf(fdr, " %s\n", word);
            fflush(fdr); // <== important
            fscanf(fdw, " %s", word);
            fflush(fdw);
            printf("The word in German: %s\n", word);
            if (strcmp(word, "Bye") == 0)
                break;
        }
    }
    fclose(fdw);
    fclose(fdr);
    unlink(FIFO_RT);
    unlink(FIFO_WT);
    return EXIT_SUCCESS;

    /* 3. when receiving messege show translation*/

    // END

    /**
     *     //    <<first we make our fifo file>> <<errno == EEXIST if fifo already exists>>
    if (mkfifo(FIFO_RT, 0666 | O_RDONLY) == -1 && errno != EEXIST)
    {
        perror("cannot create fifo file");
        exit(EXIT_FAILURE);
    }
    // open fifo>>
    if (!(fdw = fopen(FIFO_RT, "w")))
    {
        perror("cannot open fifo file for w");
        exit(EXIT_FAILURE);
    }
    */
}