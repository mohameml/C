/*
    Enoncé :

    Dans cet exercice, il n'y a rien à coder, juste à lire,
    compiler, exécuter, et comprendre l'exécution de ce programme.

    Il illustre le comportement de la fonction de libération de mémoire
    dynamique (free).

    Toto a passé un examen, il a obtenu, étonnamment, la note de 0/20.
    Par un petit tour de passe-passe, il arrive à changer sa note pour
    obtenir 10/20. Comment a-t-il fait?

    Compétences : 89,92,94
    Difficulté : 3
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /*
        On stocke la note de toto dans un entier alloué
        dynamiquement.
    */
    uint8_t* zero = malloc(sizeof(uint8_t));

    /* Toto obtient la note de 0 à l'examen. */
    *zero = 0;

    /* On le chambre un peu... */
    printf("%u + %u = la tête à Toto!\n", *zero, *zero);


    /* On n'a plus besoin de zero, on le libère. */
    free(zero);

    /* Vient ensuite le calcul de la moyenne de la classe. */
    uint8_t* moyenne = malloc(sizeof(uint8_t));


    /* Une moyenne on ne peut plus originale ! */
    * moyenne = 10;

    /* On l'annonce à tout le monde. */
    printf("Moyenne de la classe: %u/20.\n", *moyenne);

    /* Toto vient consulter sa note sur le tableau d'affichage... */
    printf("Pour mémoire, Toto a obtenu la note de %u/20.\n", *zero);

    /* On n'a plus besoin de moyenne, on la libère. */
    free(moyenne);


    return EXIT_SUCCESS;
}
