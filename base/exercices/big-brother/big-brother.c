#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Ecrit un message dans un flux passé en paramètre.
 *
 * @param stream le flux dans lequel écrire
 * @param message le message à écrire
 */
static void log_message(FILE* stream, const char* message)
{
}

int main(void)
{
    log_message(stdout, "Un message sur la sortie standard.\n");
    log_message(stderr, "Pis un autre sur la sortie d'erreurs, tiens!\n");

    FILE* f = fopen("log-secret.txt", "w");
    if (f == NULL) {
        perror("fopen log-secret.txt : ");
        exit(EXIT_FAILURE);
    }
    log_message(f, "Un dernier dans un fichier, pour la route. \
                    I am watching you.\n");
    fclose(f);

    return EXIT_SUCCESS;
}
