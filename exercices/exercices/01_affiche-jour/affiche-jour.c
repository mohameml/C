#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef enum Jour
{
    Lundi = 1,
    Mardi,
    Mrecredi,
    Jeudi,
    vendredi,
    samedi,
    dimanche

} jour;

int main(int argc, char **argv)
{
    /* Affiche un message d'erreur si l'utilisateur oublie l'argument
     * à passer en ligne de commandes. */
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s nombre\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Convertit l'argument passé par l'utilisateur en entier. */
    int32_t nombre = atoi(argv[1]);

    switch (nombre)
    {
    case Lundi:
    case Mardi:
    case Mrecredi:
    case Jeudi:
    case vendredi:
        printf("Le nombre entré correspond à un jour de semaine.\n");
        break;

    case samedi:
    case dimanche:
        printf("Le nombre entré correspond à un jour du week-end.\n");
        break;

    default:
        printf("Le nombre entré doit être compris entre 1 et 7!\n");
    }

    return EXIT_SUCCESS;
}
