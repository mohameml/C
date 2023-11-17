#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipefd[2];

    // Création du tube
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t cat_pid, wc_pid;

    // Création du processus pour la commande cat
    if ((cat_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cat_pid == 0) { // Processus fils (cat)
        // Ferme le côté écriture du tube
        close(pipefd[1]);

        // Redirige l'entrée standard vers le côté lecture du tube
        dup2(pipefd[0], STDIN_FILENO);

        // Ferme le côté lecture du tube
        close(pipefd[0]);

        // Redirige la sortie vers le fichier toto.txt
        int fd_toto = open("toto.txt", O_RDONLY);
        dup2(fd_toto, STDIN_FILENO);
        close(fd_toto);

        // Exécute la commande cat
        execlp("cat", "cat", (char *)NULL);
        perror("execlp cat");
        exit(EXIT_FAILURE);
    } else { // Processus parent
        // Création du processus pour la commande wc
        if ((wc_pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (wc_pid == 0) { // Processus fils (wc)
            // Ferme le côté lecture du tube
            close(pipefd[0]);

            // Redirige la sortie standard vers le côté écriture du tube
            dup2(pipefd[1], STDOUT_FILENO);

            // Ferme le côté écriture du tube
            close(pipefd[1]);

            // Redirige l'entrée vers le fichier titi.txt
            int fd_titi = open("titi.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd_titi, STDOUT_FILENO);
            close(fd_titi);

            // Exécute la commande wc -l
            execlp("wc", "wc", "-l", (char *)NULL);
            perror("execlp wc");
            exit(EXIT_FAILURE);
        } else { // Processus parent
            // Ferme les deux côtés du tube dans le processus parent
            close(pipefd[0]);
            close(pipefd[1]);

            // Attend que les deux processus fils se terminent
            waitpid(cat_pid, NULL, 0);
            waitpid(wc_pid, NULL, 0);
        }
    }

    return 0;
}
