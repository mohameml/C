#include<stdio.h>
#include<stdlib.h>
#include "morse.h"

/* main */
int main(void)
{
    help(); // Affiche la correspondance des caractères pris en charge et des codes Morse
    printf("Affichage du code Morse de la phrase : \"RMS Titanic SOS\"\n");
    affiche_morse("RMS Titanic SOS");
    printf("Affichage de la traduction du code Morse : \".-. -- ... // - .. - .- -. .. -.-. // ... --- ... // .---- ..... // .- ...- .-. .. .-.. // .---- ---. .---- ..---\"\n");
    affiche_texte(".-. -- ... //  - .. - .- -. .. -.-. // ... --- ... // .---- ..... // .- ...- .-. .. .-.. // .---- ---. .---- ..---");

    return EXIT_SUCCESS;
}
