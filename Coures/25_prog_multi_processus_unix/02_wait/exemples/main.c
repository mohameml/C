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
        // verifier l'état du fils 
        if(WIFEXITED(status)) 
        {
            // dans ce cas WIFEXITED(status)!=0 ,
            printf("le fils se tremine normalement !!!! \n");

            if(WEXITSTATUS(status)==0)
            {
                printf("le fils se termine par un code de retour égale à 0 -> tout va bien \n");
            }
            else
            {
                printf("Il y'a un problemen à diagnosticer car le fils se termiene par un code de retour égale à 1 \n");
            }

        }
        else
        {
            printf("le fils n'est pas termine normalement \n");
        }
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