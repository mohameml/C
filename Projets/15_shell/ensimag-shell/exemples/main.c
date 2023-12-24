#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() 
{

    while (1) 
    {
        printf("MonShell> "); // Invite de commande
        char command[BUFFER_SIZE];
        fgets(command, sizeof(command), stdin);

        if (strcmp(command, "exit\n") == 0) 
        {
            printf("Au revoir !\n");
            break; // Quitte le shell
        }

        // Crée un tuyau (pipe) pour la communication entre les processus
        int pipefd[2];
        if (pipe(pipefd) == -1) 
        {
            perror("Erreur lors de la création du tuyau");
            exit(EXIT_FAILURE);
        }

        // Fork pour créer un nouveau processus
        pid_t child_pid = fork();

        if (child_pid == -1) 
        {
            perror("Erreur lors de la création du processus enfant");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) 
        { 
            // Processus enfant
            close(pipefd[1]); // Ferme l'extrémité d'écriture du tuyau

            dup2(pipefd[0], STDIN_FILENO); // Redirige l'entrée standard vers le tuyau
            close(pipefd[0]); // Ferme l'extrémité de lecture du tuyau

            // Exécute la commande à partir de l'entrée standard
            execlp("sh", "sh", "-c", command, NULL);
            perror("Erreur lors de l'exécution de la commande");
            exit(EXIT_FAILURE);
        } 
        else 
        {
            // Processus parent
            close(pipefd[0]); // Ferme l'extrémité de lecture du tuyau
            int status;
            waitpid(child_pid, &status, 0);

            if (WIFEXITED(status)) 
            {
                printf("Le processus enfant s'est terminé avec le code de retour %d\n", WEXITSTATUS(status));
            } 
            else 
            {
                perror("Le processus enfant ne s'est pas terminé normalement");
            }
        }
    }

    return 0;

}
