#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>


int main(void)
{
    // on crée 3 pipes 
    int fd[3][2];

    for(int i = 0 ; i<3 ; i++)
    {
        if(pipe(fd[i])==-1)
        {
            printf("Errure lors de la pipe numéro %d \n",i);
            exit(1);
        }
    }


    int pid1 = fork();

    if(pid1==-1)
    {
        printf("Errure lors de la 1ére fork() \n");
    }

    if(pid1==0)
    {
        // fil1 :
        int x ;
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);

        read(fd[0][0] , &x , sizeof(int));

        x+=5 ;

        write(fd[1][1],&x , sizeof(int));
        
        close(fd[0][0]);
        close(fd[1][1]);

        return 0 ;


    }


    // paarent processus :

    int pid2 = fork();

    if(pid2 == -1)
    {
        printf("Erruer lors de la 2éme fork() \n");
    }

    if(pid2==0)
    {
        // fil 2 
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

        int x ;
        read(fd[1][0], &x , sizeof(int));
        x+=5 ;
        write(fd[2][1],&x , sizeof(int));

        close(fd[1][0]);
        close(fd[2][1]);
    
        return 0 ;
    }

    // parent processus 

    int x = 0 ;

    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    close(fd[0][0]);

    write(fd[0][1], &x , sizeof(int));

    read(fd[2][0],&x , sizeof(int));

    waitpid(pid1 , NULL , 0);
    waitpid(pid2 , NULL , 0);

    close(fd[2][0]);
    close(fd[0][1]);

    printf("la valeur de x aprés le tour est : %d \n", x);


    return 0 ;


}