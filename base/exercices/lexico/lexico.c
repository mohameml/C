#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Compare les deux lettres passées en paramètre.
 *
 * @param c1 la première lettre à comparer
 * @param c2 la deuxième lettre à comparer
 * @return int8_t un entier indiquant la relation d'ordre entre les deux lettres, à savoir :
 *         - -1 si c1 est avant c2 dans l'alphabet ;
 *         - 0 si c1 et c2 représentent la même lettre e ;
 *         - 1 si c1 est après c2 dans l'alphabet.
 */
static int8_t compare_lettres(char c1, char c2)
{
    return 0;
}

/**
 * @brief Compare les deux mots passés en paramètre.
 *
 * @param m1 le premier mot à comparer
 * @param m2 le deuxième mot à comparer
 * @return int8_t un entier indiquant la relation d'ordre entre les deux lettres, à savoir :
 *          - -1 si m1 est avant m2 selon l'ordre lexicographique ;
 *          - 0 si m1 et m2 représentent le même mot ;
 *          - 1 si m1 est après m2 selon l'ordre lexicographique.
 */
static int8_t compare_mots(const char* m1, const char* m2)
{
    return 0;
}

/**
 * @brief Teste votre fonction compare_mots(m1, m2).
 *
 * Affiche "m1 < m2" sur la sortie standard si m1 < m2,
 * "m1 > m2" si m1 > m2 et "m1 = m2" si m1 = m2.
 *
 * Je sais, c'est fou.
 *
 * @param m1 le premier mot à comparer
 * @param m2 le deuxième mot à comparer
 */
static void test_comparaison(const char* m1, const char* m2)
{
    /*
        Astuce pour contracter l'écriture de cette fonction, en remarquant que
        les valeurs de retour possibles de la fonction compare_mots() sont
        -1 (<), 0 (=) et 1 (>).

        Si on range les caractères '<', '=' et '>' dans un tableau aux index
        0, 1 et 2, il suffira de rajouter 1 à la valeur de retour de compare_mots()
        pour retrouver le caractère de comparaison qui convient pour l'affichage.

        Z'avez pas compris? On s'en tape c'est pas l'objet de l'exercice!
        Z'avez pas compris et la phrase précédente ne vous convient pas?
        Parcourez vite fait les salles machines du bâtiment E, vous trouverez
        certainement le prof qui a écrit cet exo (c'est celui qui a des lunettes).
    */
    char seps[] = "<=>";
    int8_t comparaison = compare_mots(m1, m2);

    printf("%s %c %s\n", m1, seps[comparaison + 1], m2);
}

/**
 * @brief Point d'entrée du programme.
 *
 * @return int 0 (EXIT_SUCCESS) si tout s'est bien passé
 */
int main(void)
{
    /* RIP Luis Mariano! */
    test_comparaison("lexico", "lexiiiiiiiiico");

    /* Presque pareil, non? */
    test_comparaison("lexico", "lexicoo");

    /* Non, pareil presque? */
    test_comparaison("lexicoo", "lexico");

    /* Ajoutez votre test débile ici... */
    test_comparaison("efgh", "abcd");
    test_comparaison("a", "bcd");
    test_comparaison("42", "42");

    return EXIT_SUCCESS;
}
