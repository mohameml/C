#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/types.h>
#include <stdlib.h>


int main(void)
{
    // cat < toto.txt | wc -l > titi.txt :

    // la partie cat < toto.txt 

    int fd_in = open("toto.txt" , O_RDONLY , 0644);  // ouvrir de fichier en mode lécture seulle 

    if(fd_in==-1)
    {
        perror("Erreur lors de l'ouverture  du fichier toto.txt \n");
        exit(1);
    }

    int save_in = dup(STDIN_FILENO);
    int save_out = dup(STDOUT_FILENO);

    dup2(fd_in , STDIN_FILENO);  // rédriction du stdin vers le fichier toto.txt 



    // pipe 

    int fd[2];

    if(pipe(fd)==-1)
    {
        perror("Erreur dans  pipe \n");
    }




    int id = fork();


    if(id==-1)
    {
        printf("Erruer lors de la création du procesuus fils \n");
    }



    if(id==0)
    {
        // processus fils :

        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("cat", "cat" , NULL);
    }
    else
    {
        // processu parent 
        int status ;

        wait(&status);


        if(WIFEXITED(status)==0)
        {
            perror("Error le processus fils est terminée d'une facon anormal !!! \n");
        }
        else
        {
            if(WEXITSTATUS(status)!=0)
            {
                printf("le processus est terminée avec un code de retour %d \n" , WIFEXITED(status));
            }
        }


        // la partier wc -l > titi.txt :



        int id2 = fork();


        if(id2 == -1)
        {
    
            printf("Erruer lors de la création du procesuus fils \n");

        }


        if(id2==0)
        {

            int fd_out = open("titi.txt" , O_WRONLY | O_CREAT , 0644);

            if(fd_out == -1)
            {
                printf("Erreur lors de l'ouverture du fichier titi.txt    \n");
            }

            close(fd[1]);
            dup2(fd[0] , STDIN_FILENO);
            close(fd[0]);
            execlp("wc", "wc" , "-l" , NULL);   

        }
        else
        {
            dup2()
        }


        
        


    }



    return 0 ;
}