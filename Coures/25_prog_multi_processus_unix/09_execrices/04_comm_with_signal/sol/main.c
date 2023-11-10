#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int x = 0 ;

void handel(int sig)
{
    if(x==0)
    {
    
        printf(" it is veru easy !!! : \n");

    }
}



int main(void)
{
    int id = fork();

    if(id==-1)
    {
        printf("Erreur lors lors de fork() \n");
    }

    if(id==0)
    {
        // child process 
        
        // on attend 5s ppour que l'uitilisateur répond 
        sleep(5);

        // si non 
        kill(getppid(),SIGUSR1);
    }
    else
    {
        struct sigaction sa ;
        sa.sa_handler = &handel;
        sa.sa_flags = SA_RESTART ;
        sigaction(SIGUSR1,&sa,NULL);
        // parent process 


        printf("what is the result of : 5*3 : ");
        scanf("%d",&x);

        if(x==15)
        {
            printf("Trés bien \n");
        }
        else 
        {
            printf("ce n'est pas grave, you are hiimare \n");
        }

        wait(NULL);
    }
}