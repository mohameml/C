#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>



int main(void)
{

    int fd[2];

    if(pipe(fd)==-1)
    {
        printf("Error ferom the pipe  \n");

        return 3 ;
    }
    

    int id = fork();

    if(id==-1){ return 1 ;}


    if(id==0)
    {
        // process child 
        dup2(fd[1] ,STDOUT_FILENO );
        close(fd[0]);
        close(fd[1]);

        int err = execlp("ping","ping","-c","3", "google.com",NULL);
    }


    int id2 = fork();

    if(id2==-1)
    {
        return 3 ;
    }

    if(id2==0)
    {
        dup2(fd[0],STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);  
        execlp("grep","grep","rtt", NULL);
    }


    close(fd[0]);
    close(fd[1]);
    waitpid(id, NULL, 0);
    waitpid(id2,NULL,0);
    return 0 ;
}



