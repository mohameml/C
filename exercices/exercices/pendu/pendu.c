#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* La chaine de caractères à trouver, à changer selon votre inspiration. */
    const char *a_trouver = "bounty";
    /*
        Le tampon représentant les lettres trouvées / à trouver.
        Sa taille est bien strlen(a_trouver) + 1, puisque la fonction
        strlen() retourne le nombre de caractères précédant le caractère
        de fin de chaine (\0) qu'il faut donc compter à part.
    */
    size_t taille_chaine = strlen(a_trouver) + 1;
    char tampon[taille_chaine];

    return EXIT_SUCCESS;
}
