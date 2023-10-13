#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>



int main(void)
{

    int pid = fork();


    if(pid==0)
    {
        while(1)
        {
            printf("I do somethig here  .....can you wait please ...\n");
            sleep(1);
        }
    }
    else 
    {   sleep(3);
        printf("I dont care ,  I will kill you fu** you , son of b*** ... \n");
        kill(pid,SIGKILL);
        wait(NULL);
    }




    return 0 ;
}