#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#define n 10 

int main(void)
{
    // on crée 3 pipes 
    int fd[n][2];

    int pid_list[n-1];

    for(int i = 0 ; i<n ; i++)
    {
        if(pipe(fd[i])==-1)
        {
            printf("Errure lors de la pipe numéro %d \n",i);
            exit(1);
        }
    }


    for(int i =1 ; i<n ; i++)
    {
        int pid = fork();
        

        if(pid==-1)
        {
            printf("Errure lors de la  fork() numéro %d  \n", i);
        }

        if(pid==0)
        {

            int debut1 = 0  ;
            int debu2  = i+1 ;
            int end1 = i;
            int end2 = n;
            int lecture  = i-1 ;
            int écriture  = i ;
            // closing


            for(int j = debut1 ; j < end1 ; j++)
            {
                close(fd[j][0]);
                close(fd[j][1]);
            } 

            for(int k = debu2  ; k < end2  ; k++ )
            {
                close(fd[k][0]);
                close(fd[k][1]);
            }

            close(fd[lecture][1]);
            close(fd[écriture][0]);

            // opérations : 

            int x ;

            read(fd[lecture][0] , &x , sizeof(int));

            x+=1 ;

            write(fd[écriture][1],&x , sizeof(int));
            
            close(fd[lecture][0]);
            close(fd[écriture][1]);

            return 0 ;


        }
        else 
        {
            pid_list[i]= pid ;
        }
    }




    // paarent processus :

    int x = 0 ;


    // closing


    for(int j = 1 ; j < n-1 ; j++)
    {
        close(fd[j][0]);
        close(fd[j][1]);
    } 

    close(fd[0][0]);
    close(fd[n-1][1]);

    write(fd[0][1], &x , sizeof(int));

    for(int i =0 ; i<n-1 ; i++)
    {
        waitpid(pid_list[i], NULL , 0);
    }
    
    read(fd[n-1][0] , &x , sizeof(int));





    close(fd[n-1][0]);
    close(fd[0][1]);

    printf("la valeur de x aprés le tour est : %d \n", x);


    return 0 ;


}

