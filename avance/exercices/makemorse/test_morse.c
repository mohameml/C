#include <stdio.h>
#include <stdlib.h>
#include "morse.h"

int main(void)
{
    /* Chaine de caractères à encoder en morse. */
    const char *message = "RMS Titanic SOS";

    /*
        Code morse à déchiffrer. Le caractère '\' indique que la définition
        de la chaine de caractères continue à la ligne suivante.
    */
    const char *code_morse = ".-. -- ... // - .. - .- -. .. -.-. // \
                              ... --- ... // .---- ..... // \
                              .- ...- .-. .. .-.. // .---- ---. .---- ..---";

    /*
        Affiche la correspondance des caractères pris en charge
        et des codes morse.
    */
    help();

    /* Allez, au boulot! */
    printf("Affichage du code Morse de la phrase : %s\n", message);
    affiche_morse(message);
    printf("Affichage de la traduction du code Morse : %s\n", code_morse);
    affiche_texte(code_morse);

    return EXIT_SUCCESS;
}
