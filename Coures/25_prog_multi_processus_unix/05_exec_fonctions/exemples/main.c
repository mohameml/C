#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>



int main(void)
{

    int id = fork();

    if(id==0)
    {
        // processs child 
        int err = execlp("ping","ping","-c","3","google.com",NULL);

        if(err==-1)
        {
            printf("we can not find the programme \n");

            return 0 ;
        }
    }
    else
    {
        int status ;
        wait(&status);

        if(WIFEXITED(status))
        {
            // ie le child se termine normalement :
            int statuscode = WEXITSTATUS(status);

            if(statuscode==0)
            {
                printf("our child executed with sucssaful  !! \n");
            }
            else 
            {
                printf("FAILURE \n");
            }
        }

    }



    
    return 0 ;
}