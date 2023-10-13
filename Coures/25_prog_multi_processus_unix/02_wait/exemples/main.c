#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(void)
{
    int id = fork();

    int n ;

    if(id==0)
    {
        n = 1 ;
    }
    else 
    {
        int status ; //  Variable pour stocker le statut de sortie du processus fils
        wait(&status);
        n = 6 ;
    }

    for(int i = n ; i<n+5 ; i++)
    {
        printf("%d ",i);
    }

    if(id!=0)
    {
        printf("\n");

    }



    return 0 ;
}