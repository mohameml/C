#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_JOBS 10

typedef struct {
    pid_t pid;
    char command[MAX_INPUT_SIZE];
} Job;

Job jobs[MAX_JOBS];
int job_count = 0;

void execute_command(char *command, int background) {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processus fils
        char *args[MAX_INPUT_SIZE];
        int i = 0;

        char *token = strtok(command, " ");

        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        if (background) {
            signal(SIGINT, SIG_IGN); // Ignorer les signaux SIGINT (Ctrl+C) dans les processus en arrière-plan
        }

        execvp(args[0], args);

        perror("execvp"); // En cas d'échec de l'exécution de la commande
        exit(EXIT_FAILURE);
    } else { // Processus parent
        if (!background) 
        {
            int status;
            waitpid(pid, &status, 0);
        } else {
            printf("Processus fils créé avec PID %d en arrière-plan.\n", pid);
            // Ajouter le travail à la liste des travaux
            if (job_count < MAX_JOBS) {
                jobs[job_count].pid = pid;
                strcpy(jobs[job_count].command, command);
                job_count++;
            } else {
                printf("Nombre maximal de travaux atteint. Ne peut pas ajouter de nouveau travail.\n");
            }
        }
    }
}

void list_jobs() 
{
    printf("Liste des processus en arrière-plan :\n");
    for (int i = 0; i < job_count; i++) {
        int status;
        pid_t result = waitpid(jobs[i].pid, &status, WNOHANG);

        if (result == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        } else if (result == 0) {
            // Le processus n'est pas encore terminé
            printf("[%d] PID: %d - Commande: %s (En cours d'exécution)\n", i + 1, jobs[i].pid, jobs[i].command);
        } else {
            // Le processus s'est terminé
            printf("[%d] PID: %d - Commande: %s (Terminé)\n", i + 1, jobs[i].pid, jobs[i].command);
            // Supprimer le travail de la liste des travaux
            for (int j = i; j < job_count - 1; j++) 
            {
                jobs[j] = jobs[j + 1];
            }
            job_count--;
        }
    }
}

int main() {
    while (1) {
        char input[MAX_INPUT_SIZE];
        printf("minishell> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        // Supprimer le saut de ligne de la fin de la commande
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Vérifier si la commande doit être exécutée en arrière-plan
        int background = 0;
        if (input[strlen(input) - 1] == '&') {
            background = 1;
            input[strlen(input) - 1] = '\0'; // Supprimer le '&'
        }

        // Quitter le shell si l'utilisateur entre "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strcmp(input, "jobs") == 0) {
            // Liste des travaux en arrière-plan
            list_jobs();
        } else {
            // Exécuter la commande
            execute_command(input, background);
        }
    }

    return 0;
}
