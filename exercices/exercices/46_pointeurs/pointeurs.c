#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    // Interdit de changer la ligne qui suit !
    uint8_t target = 123;

    /*
        Déclarer ci-dessous un pointeur appelé ptr
        et l'initialiser de manière à ce qu'il référence
        la variable target.
    */
    // TODO

    /*
        Changer la valeur de target pour 255 par l'intermédiaire
        du pointeur ptr. Autrement dit, vous n'avez pas le droit
        ici d'écrire "target = 255;".
    */
    // TODO

    // Doit afficher "La valeur de target est 255."
    printf("La valeur de target est %u.\n", target);

    return EXIT_SUCCESS;
}