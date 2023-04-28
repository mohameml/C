#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NB_ETUS 7

/* Structure de données représentant un étudiant. */
struct etu {
    /* Nom de l'étudiant. */
    char *nom;
    /* Son score, sur 100. */
    float score;
};

/* Affiche le tableau d'étudiants passé en paramètre. */
static void afficher_etudiants(struct etu diants[NB_ETUS]) {
    for (size_t i = 0; i < NB_ETUS; i++) {
        printf("%s: %2.1f\n", diants[i].nom, diants[i].score);
    }
}


int main(void)
{
    struct etu diants[NB_ETUS] = {
        { "François", 44.1 },
        { "Jean-Frédéric", 1.5 },
        { "Alain", 28.6 },
        { "Bruno", 2.4},
        { "Nicolas", 20.7 },
        { "Nathalie", 2.6 },
        { "Jean-François", 0.3 }
    };

    /* TODO : On trie les étudiants en fonction de leurs notes en utilisant qsort() */
    printf("Classés par notes croissantes :\n");
    afficher_etudiants(diants);

    /* TODO : On trie les étudiants par ordre alphabétique en utilisant qsort() */
    printf("\nClassés par ordre alphabétique :\n");
    afficher_etudiants(diants);

    return EXIT_SUCCESS;
}
