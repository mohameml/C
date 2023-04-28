/*
    Enoncé :

    L'objectif de cet exercice est de compiler à la main
    (c'est-à-dire sans utiliser de Makefile) un programme C qui fait
    appel à une bibliothèque externe.

    Une fois cette prouesse accomplie, on vous demande aussi d'écrire
    un Makefile qui automatise la génération de l'exécutable
    compile-toi.

    Attention, les deux solutions doivent être abordées et comprises
    (compilation à la main + Makefile).

    Compétences : 9,10,79
    Difficulté : 1
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("La racine carrée de 427 est %g.\n", sqrt(427));
    return EXIT_SUCCESS;
}

