# Enoncé

Dans cet exercice, il n'y a rien à coder, juste à lire, compiler,
exécuter, et comprendre l'exécution de ce programme.

Il illustre le comportement de la fonction de libération de mémoire
dynamique (`free`).

Toto a passé un examen, il a obtenu, étonnamment, la note de 0/20.
Par un petit tour de passe-passe, il arrive à changer sa note pour
obtenir 10/20. Comment a-t-il fait?

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/triche/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* afficher la valeur du pointeur zero avant et après libération.
* afficher la valeur du pointeur moyenne et la comparer à celle du
pointeur zero.

</details>

# Compétences

* Opérateur d'indirection
* Allocation de mémoire dynamique type de donnée simple
* Libération de mémoire

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: triche

.PHONY: clean
clean:
	rm -f *~ *.o triche

```

#### Corrigé du fichier triche.c

```c
/*
    Enoncé :

    Dans cet exercice, il n'y a rien à coder, juste à lire,
    compiler, exécuter, et comprendre l'exécution de ce programme.

    Il illustre le comportement de la fonction de libération de mémoire
    dynamique (free).

    Toto a passé un examen, il a obtenu, étonnamment, la note de 0/20.
    Par un petit tour de passe-passe, il arrive à changer sa note pour
    obtenir 10/20. Comment a-t-il fait?

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /*
        On stocke la note de toto dans un entier alloué
        dynamiquement.
    */
    uint8_t* zero = malloc(sizeof(uint8_t));
    printf("Valeur de zero apres le malloc = %p\n", zero);

    /* Toto obtient la note de 0 à l'examen. */
    *zero = 0;

    /* On le chambre un peu... */
    printf("%u + %u = la tête à Toto!\n", *zero, *zero);

    /*
        Pour libérer une zone mémoire allouée dynamiquement, on passe
        un pointeur vers cette zone mémoire à la fonction free().

        En pratique, on va marquer la zone mémoire pointée comme étant
        réutilisable par le système d'exploitation pour une allocation
        dynamique future.

        En revanche, le pointeur passé en paramètre de la fonction free
        n'est pas modifié. Pour s'en convaincre, sans même exécuter le
        programme et afficher la valeur du pointeur zero avant et après
        libération, il suffit de raisonner sur le prototype de la
        fonction free. Si la fonction free souhaitait modifier le
        pointeur (void *) passé en paramètre, pour par exemple le
        passer à la valeur NULL, il faudrait passer l'adresse de ce
        pointeur en paramètre, et non le pointeur directement. On
        aurait alors un prototype de ce style: void free(void **ptr);
        En effet, les paramètres d'une fonction C sont passés par
        valeur, il y a donc une copie implicite des paramètres en
        entrée de la fonction, et on travaille ensuite sur des
        copies. Affecter directement un paramètre de fonction revient
        donc à affecter sa copie, qui sera détruite en sortie de
        fonction. Si tout ça n'est pas clair pour vous, relisez la
        fiche sur le passage de paramètres (exemple echange(a,b)).

        Au final, free(zero) libère la zone mémoire pointée par zero,
        mais le pointeur zero pointe toujours sur la même adresse mémoire.
    */

    /* On n'a plus besoin de zero, on le libère. */
    free(zero);
    printf("Valeur de zero apres free(zero) = %p\n", zero);

    /* Vient ensuite le calcul de la moyenne de la classe. */
    uint8_t* moyenne = malloc(sizeof(uint8_t));
    printf("Valeur de moyenne apres malloc = %p\n", moyenne);

    /*
        Ici, on demande au système d'exploitation d'allouer
        dynamiquement une zone mémoire pouvant stocker un entier 8
        bits. Il se trouve qu'on vient tout juste de libérer une zone
        mémoire de même taille (free(zero)). L'allocateur décide souvent
        d'allouer ce nouvel entier dans l'emplacement précédemment
        occupé par l'entier pointé par zero. Autrement dit, on a
        maintenant deux pointeurs qui pointent vers la même zone
        mémoire: zero et moyenne.

        Ce qui signifie que lorsqu'on modifie *moyenne, on modifie
        *zero!

        NOTA BENE 1 : Après un free, même si l'adresse d'une variable
        libérée reste la même, l'ancien contenu de la variable peut
        être remis à 0 ou pas (cela dépend du système/compilateur utilisé).
        Ce contenu peut aussi prendre une valeur indéfinie si la zone mémoire
        concernée fait l'objet d'une autre utilisation par le système et ses
        autres programmes en cours.
        L'observation des contenus des variables après les free permet
        de vérifier ce qu'il en est.

        NOTA BENE 2 : Cette allocation dans l'emplacement précédemment
        libéré est le cas le plus souvent constaté avec ce programme
        d'exemple. Toutefois, ce n'est pas systématique à 100% et un
        autre emplacement mémoire peut parfois être alloué.
        L'observation des adresses des variables après allocation et free
        des variables zero et moyenne permet de vérifier si c'est
        effectivement le cas ou pas.
     */

    /* Une moyenne on ne peut plus originale ! */
    * moyenne = 10;

    /* On l'annonce à tout le monde. */
    printf("Moyenne de la classe: %u/20.\n", *moyenne);

    /* Toto vient consulter sa note sur le tableau d'affichage... */
    printf("Pour mémoire, Toto a obtenu la note de %u/20.\n", *zero);

    /* On n'a plus besoin de moyenne, on la libère. */
    free(moyenne);

    printf("Valeur de zero apres free(moyenne) = %p\n", zero);
    printf("Valeur de *zero apres free(moyenne) = %u\n", *zero);
    printf("Valeur de moyenne apres free(moyenne) = %p\n", moyenne);
    printf("Valeur de *moyenne apres free(moyenne) = %u\n", *moyenne);

    return EXIT_SUCCESS;
}

```


</details>
