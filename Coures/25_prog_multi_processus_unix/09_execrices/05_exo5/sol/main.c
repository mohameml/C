#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{

    int fd[2];
    
    if(pipe(fd)==-1)
    {
        exit(1);
    }
    

    int id = fork() ;

    if(id==-1)
    {
        exit(1);
    }


    if(id==0)
    {
        // child process 
        close(fd[0]);
        char str[200];
        printf("ecriviez votre message ici : \n");
        fgets(str, sizeof(str), stdin);

        str[strlen(str) -1 ] = '\0';

        printf("--> %s \n",str);
        
    
        write(fd[1] , str , sizeof(str));
        close(fd[1]);
    }
    else 
    {
        //  father process 
        wait(NULL);
        close(fd[1]);
        char str[200];
        read(fd[0],str , sizeof(str));
        printf("--> %s \n",str);
        printf("Recvied from the chiled:  \n  %s \n",str);


        close(fd[0]);
    }

}