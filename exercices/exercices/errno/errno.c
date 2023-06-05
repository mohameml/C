#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Ouvre un fichier selon un mode passé en paramètre.
 *
 * @param filename le chemin d'accès au fichier à ouvrir
 * @param mode le mode dans lequel ouvrir le fichier (cf man fopen)
 * @return FILE* le fichier ouvert
 */
static FILE* ouvrir_fichier(const char* filename, const char* mode)
{
    FILE* fichier = fopen(filename, mode);
    return fichier;
}

/**
 * @brief Ferme le fichier passé en paramètre.
 *
 * @param fichier le fichier à fermer
 */
static void fermer_fichier(FILE* fichier)
{
    int ret = fclose(fichier);
}

/**
 * @brief Affiche un message explicitant comment utiliser le programme
 *
 * @param progname le nom du programme
 */
static void usage(const char* progname)
{
    /* On commence par râler... */
    fprintf(stderr, "Usage: %s n\n", progname);
    fprintf(stderr, "\toù n l'entier 1 ou 2.\n");
    /* ... puis on s'en va en claquant la porte. (la fonction exit(code) permet
     * de quitter le programme avec le code de retour passé en paramètre.)*/
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    /* argv est un tableau de chaines de caractères, de taille argc, dont
     * chaque élément est un mot de la ligne de commande. Ainsi, argv[0]
     * représente le nom du programme, argv[1] le premier argument. */
    if (argc != 2) {
        /* On doit obligatoirement saisir un numéro de scénario sur la ligne
         * de commande. */
        usage(argv[0]);
    }

    /* On convertit l'argument en ligne de commande, qui est une chaine de
     * caractères en C, en entier. */
    uint8_t id = atoi(argv[1]);

    /* On aurait pu faire un switch() ici. */
    if (id == 1) {
        /* Premier scénario. */
        FILE* lecture_seule = ouvrir_fichier("lecture-seule.txt", "w");
        fermer_fichier(lecture_seule);
    } else if (id == 2) {
        /* Deuxième scénario. */
        FILE* inexistant = ouvrir_fichier("t-es-pas-la-mais-t-es-ou.txt", "r");
        fermer_fichier(inexistant);
    } else {
        /* Le numéro de scénario n'est pas bon, on râle. */
        usage(argv[0]);
    }

    return EXIT_SUCCESS;
}
