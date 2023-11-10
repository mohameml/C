#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
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
        



        if(err==-1)
        {
            printf("error \n");
            return 2 ;
        }

        

    }
    else 
    {
        int status ;
        wait(&status);
        
        if(WIFEXITED(status))
        {
            int statuscode = WEXITSTATUS(status);

            if(statuscode==0)
            {
                printf("Sucesses \n");
            }
            else
            {
                printf("Error \n");
            }
        }

        

        dup2(fd[0],STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);  
        execlp("grep","grep","rtt", NULL);





    }







    return 0 ;
}



