# Énoncé

L'objectif de cet exercice est de calculer la somme des 10 premiers
entiers pairs positifs (0 compris). On utilisera un tableau pour
stocker ces entiers, et on calculera ainsi la somme de ses éléments.
Le résultat sera affiché sur la sortie standard.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/somme-pairs/`.

# Ressources associées

La fiche [Structures de contrôle](http://formationc.pages.ensimag.fr/prepa/prof/kit/ctrl/) vous apprendra à écrire une boucle `for`.

Ça doit valoir le coup de lire la fiche [Tableaux](http://formationc.pages.ensimag.fr/prepa/prof/kit/tableaux/), aussi.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

Initialisation d'un tableau (voir page 36 du poly)
Parcours des éléments avec une boucle for
</details>

# Compétences

* Tableaux statiques
* Boucles for
* Boucles while

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: somme-pairs

.PHONY: clean
clean:
	rm -f *~ *.o somme-pairs

```

#### Corrigé du fichier somme-pairs.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
/*
    Ici, le nombre d'éléments du tableau est relativement petit.  On peut donc
    l'initialiser directement à l'aide de la notation :
*/
    uint8_t tab[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };

/*
    Cette écriture permet de ne pas spécifier la taille du tableau quand on le
    déclare. Elle sera automatiquement détectée par le compilateur.
    Si on ne fait pas ça, on peut toujours déclarer un tableau de 10 éléments et
    les initialiser un à un :
        uint8_t tab[10];
        tab[0] = 0;
        tab[1] = 2;
        tab[2] = 4;
        tab[3] = 6;
        tab[4] = 8;
        tab[5] = 10;
        tab[6] = 12;
        tab[7] = 14;
        tab[8] = 16;
        tab[9] = 18;

    Ou, de manière plus concise :
        uint8_t tab[10];
        for (uint8_t i = 0; i < 10; i++) {
            tab[i] = 2*i;
        }
*/
    uint8_t somme = 0;
    for (uint8_t i = 0; i < 10; i++) {
        somme += tab[i];
    }

    printf("Valeur attendue: %u.\n", somme);

    return EXIT_SUCCESS;
}

```


</details>
