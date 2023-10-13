#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>




int main(void)
{
    int fd[2];

    int status = pipe(fd);

    if(status==-1)
    {
        perror("Error fro the opening the pipe \n");
    }


    int id = fork();

    if(id==0)
    {
        // the child processus 
        // chlid will write in the pipe
        close(fd[0]); // closing the file descritption of raeding in the pipe 
        int x ;
        printf("Please write your number : ");
        scanf("%d",&x);
        write(fd[1], &x , sizeof(int));
        close(fd[1]); // in the end , you must closing the file descritpion of writhing in the pipe 
    }
    else 
    {
        // the case of the parent processus 
        close(fd[1]);
        int y ;
        read(fd[0], &y , sizeof(int));
        close(fd[0]);
        printf("Got from the processus child in the pipe %d \n", y);
    }

    return 0 ;
}