#include <stdlib.h>
#include <stdio.h>

#ifdef DOUBLE_PREC
#define MESSAGE "Mode double\n"
#else
#define MESSAGE "Mode float\n"
#endif /* DOUBLE_PREC */

int main(int argc, char **argv)
{
    /* Affiche un message d'erreur si l'utilisateur oublie l'argument
     * à passer en ligne de commandes. */
    if (argc < 3) {
	fprintf(stderr, "Usage: %s x y\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    printf(MESSAGE);

    /* Convertit le premier argument passé par l'utilisateur en entier. */
    int x = atoi(argv[1]);

    /* Convertit le deuxième argument passé par l'utilisateur en entier. */
    int y = atoi(argv[2]);

    /* On effectue la division! */
    float res = (float)x / (float)y;

    /*
	On affiche le résultat avec jusqu'à 20 chiffres
	avant la virgule et jusqu'à 18 chiffres après la virgule.
    */
    printf("%d / %d = %20.18f\n", x, y, res);

    return EXIT_SUCCESS;
}
