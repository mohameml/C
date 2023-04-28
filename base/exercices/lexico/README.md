# Enoncé

On implémente ici quelque chose qui ressemble à la fonction standard
`strcmp()`, à savoir un programme qui compare deux chaines de caractères.

Pour ce faire, on vous demande d'implémenter une fonction `compare_lettres()`
qui compare deux caractères selon l'ordre lexicographique, puis d'utiliser
cette fonction pour implémenter une fonction `compare_mots()` dont le
prototype et le comportement est identique à la fonction `strcmp()`.

Le cahier des charges de ces fonctions est donné en commentaires dans le
squelette de code ci-dessous.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/lexico/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* `man ascii`, ascii sur google et tout et tout ;
* `man strcmp` pour comprendre ce qu'on cherche à faire.
</details>

# Compétences

* Opérateurs de comparaison
* Traitement caractère par caractère
* Codage ASCII

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: lexico

.PHONY: clean
clean:
	rm -f *~ *.o lexico

```

#### Corrigé du fichier lexico.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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
    /*
        En C, un caractère est codé sous la forme d'un entier 8 bits.
        La valeur de cet entier est en fait un index dans une table qui fait
        la correspondance entre valeur entière et caractère : la table ASCII.

        Si vous jetez un oeil à cette table (par exemple en tapant man ascii
        dans votre terminal), vous vous rendrez compte avec l'oeil qui vous reste
        que les index des lettres de l'alphabet sont rangés selon l'ordre
        lexicographique : on retrouve 'a' à l'index 97, 'b' à l'index 98
        et ainsi de suite.

        On peut utiliser cette caractéristique pour déterminer facilement si
        un caractère est placé avant ou après un autre selon l'ordre lexicographique :
        il suffit de comparer leurs index, c'est-à-dire leurs valeurs directement.
    */
    if (c1 < c2) {
        /*
            L'index de c1 est inférieur à l'index de c2, donc c1 apparait avant c2
            selon l'ordre lexicographique.
        */
        return -1;
    }

    if (c1 > c2) {
        /*
            L'index de c1 est supérieur à l'index de c2, donc c1 apparait après c2
            selon l'ordre lexicographique.
        */
        return 1;
    }

    /*
        L'index de c1 est égal à l'index de c2, donc c1 et c2
        représentent le même caractère.
    */
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
    /*
        Si les mots sont de tailles différentes, on itère sur
        les caractères du mot le plus petit.
    */
    size_t size1 = strlen(m1);
    size_t size2 = strlen(m2);

    /*
        Ecriture contractée du minimum entre deux valeurs utilisant
        l'opérateur d'affectation ternaire :
        truc = condition ? val1 si (condition == true) : val2 si (condition == false);
    */
    size_t min_size = size1 < size2 ? size1 : size2;

    /*
        On teste les caractères 2 à 2.

        Attention, astuce "ceinture noire en ASCII" ici!
        On itère sur toutes les lettres de la chaine la plus petite,
        _y compris le caractère de fin de chaine (\0)_, d'où le i <= min_size
        en condition d'arrêt de la boucle.

        Comme ça, quand on arrive sur le caractère de fin de chaine, on compare
        sa valeur avec celle du caractère en même position dans l'autre chaine.
        Et comme la valeur de '\0' est 0 (cf man ascii), 0 est toujours inférieur
        à la valeur de n'importe quel caractère autre que \0, et on s'arrête!

        Vous avez pas compris? Allez faire un tour sur : https://www.youtube.com/watch?v=qMkFM6xIPQ4
    */
    for (size_t i = 0; i <= min_size; i++) {
        if (m1[i] != m2[i]) {
            return compare_lettres(m1[i], m2[i]);
        }
    }

    /* Si on est ici, c'est qu'on n'a trouvé aucune différence. */
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

```


</details>
