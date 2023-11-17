#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void affiche_et_libere_tab(uint8_t** tab, uint8_t taille, uint8_t offset){
    /* Affiche la ligne courante */
    uint8_t i;
    for(i = 0; i < taille; i++) {
	printf("%3u ", tab[taille - offset][i]);
    }
    printf("\n");
    /* libere la memoire associee a la ligne qui vient d'etre lue */
    free(tab[taille - offset]);
    /* Affiche le reste du tableau par recursion */
    if (offset > 0) {
	affiche_et_libere_tab(tab, taille, offset - 1);
    }
}

int main(void)
{
    /* Construit un simple tableau a deux dimmensions contenant les tables de
     * multiplications
     */
    uint8_t taille = 10;
    uint8_t **tab = malloc(taille * sizeof(uint8_t *));
    uint8_t i, j;
    for(i = 0; i < taille; i++) {
	tab[i] = malloc(taille * sizeof(uint8_t));
	for(j = 0; j < taille; j++) {
	    tab[i][j] = (i + 1) * (j + 1);
	}
    }
    /* On affiche notre tableau */
    affiche_et_libere_tab(tab, taille, taille);
    /* On libere le dernier pointeur */
    free(tab);

    return EXIT_SUCCESS;
}
