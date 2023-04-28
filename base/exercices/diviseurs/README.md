# Énoncé

Il vous est demandé d'implémenter un programme qui prend un nombre entier
strictement positif `N` en paramètre et qui affiche la liste de ses
diviseurs, différents de 1 ou de lui-même, ou `"N est premier!"` si le nombre
passé en paramètre n'a pas d'autres diviseurs que 1 et lui-même.

Pas d'inquiétude, il n'y a pas de maths complexes ici : on va
simplement énumérer tous les entiers `k` de l'intervalle `[2; N-1]` et
tester si le reste de la division entière de `N` par `k` est 0 ou non.

Voici deux exemples de sortie de ce programme :

```
./diviseurs 13
13 est premier !

./diviseurs 112
2 est un diviseur de 112.
4 est un diviseur de 112.
7 est un diviseur de 112.
8 est un diviseur de 112.
14 est un diviseur de 112.
16 est un diviseur de 112.
28 est un diviseur de 112.
56 est un diviseur de 112.
```

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/diviseurs/`.

# Ressources associées

La fiche de cours sur les [opérateurs C](http://formationc.pages.ensimag.fr/prepa/prof/papl/operateurs) rappelle tous les opérateurs arithmétiques parmi lesquels vous trouverez ceux qu'il faudra utiliser.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* En C, on calcule le reste de la division entière de deux entiers avec l'opérateur `%`
</details>

# Compétences

* Entiers
* Opérateurs arithmétiques
* Affichage formaté sur la sortie standard
* Boucles for

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: diviseurs

.PHONY: clean

clean:
	rm -f *~ *.o diviseurs

```

#### Corrigé du fichier diviseurs.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    /* Affiche un message d'erreur si l'utilisateur oublie l'argument
     * à passer en ligne de commandes. */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s nombre\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Convertit l'argument passé par l'utilisateur en entier non signé. */
    int32_t au_cas_ou = atoi(argv[1]);
    if (au_cas_ou < 1) {
        fprintf(stderr, " on a dit \"strictement positif\", le nombre! Pas %d...\n", au_cas_ou);
        exit(EXIT_FAILURE);
        /* Tiens et si ca tient pas sur 32 bits? A voir... */
    }
    uint32_t nombre = (uint32_t) au_cas_ou;

    /* On compte le nombre de diviseurs entre 2 et nombre-1 */
    uint32_t nb_diviseurs = 0;
    for (uint32_t n = 2; n < nombre; n++) {
        /* % est l'opérateur modulo. */
        if (nombre % n == 0) {
            printf("%u est un diviseur de %u.\n", n, nombre);
            nb_diviseurs++;
        }
    }

    if (nb_diviseurs == 0) {
        printf("%u est premier!\n", nombre);
    }

    return EXIT_SUCCESS;
}

```


</details>
