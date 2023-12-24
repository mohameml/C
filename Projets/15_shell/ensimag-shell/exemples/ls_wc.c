#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];

    // Création du tube
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t ls_pid, wc_pid;

    // Création du processus pour la commande ls
    if ((ls_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (ls_pid == 0) { // Processus fils (ls)
        // Ferme le côté lecture du tube
        close(pipefd[0]);

        // Redirige la sortie standard vers le côté écriture du tube
        dup2(pipefd[1], STDOUT_FILENO);

        // Ferme le côté écriture du tube
        close(pipefd[1]);

        // Exécute la commande ls
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else { // Processus parent
        // Création du processus pour la commande wc -l
        if ((wc_pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (wc_pid == 0) { // Processus fils (wc -l)
            // Ferme le côté écriture du tube
            close(pipefd[1]);

            // Redirige l'entrée standard vers le côté lecture du tube
            dup2(pipefd[0], STDIN_FILENO);

            // Ferme le côté lecture du tube
            close(pipefd[0]);

            // Exécute la commande wc -l
            execlp("wc", "wc", "-l", (char *)NULL);
            perror("execlp wc");
            exit(EXIT_FAILURE);
        } else { // Processus parent
            // Ferme les deux côtés du tube dans le processus parent
            close(pipefd[0]);
            close(pipefd[1]);

            // Attend que les deux processus fils se terminent
            waitpid(ls_pid, NULL, 0);
            waitpid(wc_pid, NULL, 0);
        }
    }

    return 0;
}
