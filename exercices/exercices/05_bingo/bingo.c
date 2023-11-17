#include <stdlib.h>
#include <stdint.h>

/* Alloue et initialise un tableau contenant la suite des entiers
 * naturels strictement positifs de l'intervalle [1; val_max] rangés à
 * des positions aléatoires. */
static uint32_t *generer_tab_aleatoire(uint32_t val_max)
{
    uint32_t *tab = NULL;

    return tab;
}

int main(void)
{
    uint32_t val = 42;
    uint32_t *tab = generer_tab_aleatoire(512);

    /* A compléter */
    /* Consigne: cette ligne doit rester la dernière du programme. */
    free(tab);

    return EXIT_SUCCESS;
}
