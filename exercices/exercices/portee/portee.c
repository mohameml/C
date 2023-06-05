#include <stdlib.h>
#include <stdio.h>

#include "point.h"

void afficher(int argc, char **argv)
{
    for (int i = 0; i < argc; i++) {
        printf("argument %i: %s\n", i, argv[i]);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s coordX coordY\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Affichage pour du debug... */
    afficher(argc, argv);

    struct point p;
    p.x = atoi(argv[1]);
    p.y = atoi(argv[2]);

    double d = distance_origine(p);
    printf("Distance de ce point à l'origine: %lf.\n", d);

    return EXIT_SUCCESS;
}
