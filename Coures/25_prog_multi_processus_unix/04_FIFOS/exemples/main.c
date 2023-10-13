#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(void)
{

    // to carte a fifo 
    mkfifo("myfifo1",0777);

    printf("opening .... \n");
    int fd = open("myfifo1",O_WRONLY);
    printf("opened\n");
    if(fd==-1)
    {
        return 1 ;
    }

    int x = 'Z';
    

    printf("writing ...\n");
    write(fd,&x,sizeof(x));

    close(fd);

    printf("closed\n");

    return 0 ; 
}