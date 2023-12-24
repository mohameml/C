#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    char saisie[3];
    uint16_t value;
    printf("Je lis dans vos pensees.\nPensez a un chiffre entre 0 et 2.\nTapez le au clavier, je ne regarde pas !\n");
    fgets(saisie, 3, stdin);
    value = atoi(saisie);
    if (value = 0) {
        printf("Vous avez saisi la valeur 0\n");
    }
    if (value = 1) {
        printf("Vous avez saisi la valeur 1\n");
    }
    if (value = 2) {
        printf("Vous avez saisi la valeur 2\n");
    }
    return EXIT_SUCCESS;
}
