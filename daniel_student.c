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

int main(int argc, char *argv[])
{
    /*might need this*/
    // char *cptr = NULL, exitstr = {"exit"};
    /* 1. open reader and writer fifo recpectively*/
    char word[STR_LEN];
    FILE *descriptor_write;
    FILE *descriptor_read;


    /*write*/
    if (!(descriptor_read = fopen(FIFO_WRITE_T, "w")))
    {
        perror("cannot open fifo file for w");
        exit(EXIT_FAILURE);
    }

    printf("******************\n");
    puts("Enter English Word: ");
    /* 2. recive strings from user until receiving "exit" */
    while (fgets(word, STR_LEN, stdin) != NULL)
    {
        fprintf(descriptor_read, " %s\n", word);
        fflush(descriptor_read); // <== important
        fscanf(descriptor_write, " %s", word);
        fflush(descriptor_write);
        printf("The word in German: %s\n", word);
    }
    fclose(descriptor_write);
    fclose(descriptor_read);
    unlink(FIFO_READ_T);
    unlink(FIFO_WRITE_T);
    return EXIT_SUCCESS;

    /* 3. when receiving messege show translation*/

    // END

    /**
     *     //    <<first we make our fifo file>> <<errno == EEXIST if fifo already exists>>
    if (mkfifo(FIFO_READ_T, 0666 | O_RDONLY) == -1 && errno != EEXIST)
    {
        perror("cannot create fifo file");
        exit(EXIT_FAILURE);
    }
    // open fifo>>
    if (!(descriptor_write = fopen(FIFO_READ_T, "w")))
    {
        perror("cannot open fifo file for w");
        exit(EXIT_FAILURE);
    }
    */
}