#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Vérifie que les arguments passés en ligne de commande sont conforme.
 *
 * Affiche un message d'usage si ce n'est pas le cas.
 *
 * @param argc la longueur du tableau argv
 * @param argv les arguments à analyser, sous la forme d'un tableau de chaines de caractères
 */
static void verif_params(int argc, char** argv)
{
    if (argc != 4 || atoi(argv[3]) < 1 || atoi(argv[3]) > 25) {
        fprintf(stderr, "Usage: %s input.txt output.txt key\n", argv[0]);
        fprintf(stderr, "où:\n");
        fprintf(stderr, "\t- input.txt est le nom du fichier texte a coder ;\n");
        fprintf(stderr, "\t- output.txt est le nom du fichier dans lequel enregistrer le texte codé ;\n");
        fprintf(stderr, "\t- key est un entier compris entre 1 et 25.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Encode une lettre en appliquant une rotation (codage de Cesar).
 *
 * @param c la lettre à encoder
 * @param cle la rotation à appliquer
 * @return char la lettre résultant de la rotation de c de cle positions
 */
static char coder_lettre(char c, uint8_t cle)
{
    /* Pour que le compilateur soit content. */
    return c;
}


int main(int argc, char** argv)
{
    verif_params(argc, argv);


    return EXIT_SUCCESS;
}
