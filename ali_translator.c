#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    /*creat twofifos -if needed-*/
    int fd[2];
    char myfifos[2];
    char *myfifo = "/tmp/myfifo";

    /*wait for in-coming requests from student-s-*/
    while (1){
        //read from fifo
    }
    /*creat thread to read request*/

    //when getting exit:
    /*print bye*/

    /*join thrid*/
    //
}