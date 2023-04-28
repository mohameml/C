# Enoncé

Au menu de cet exercice: des boucles, un soupçon d'allocation
dynamique et un poil de génération de nombres aléatoires.

Dans un premier temps, il vous est demandé d'implémenter la fonction:

```c
uint32_t *generer_tab_aleatoire(uint32_t val_max);
```

qui alloue et initialise un tableau de `val_max` entiers naturels
strictement positifs. Ce tableau contiendra la suite des entiers de 1
à `val_max` rangés de manière aléatoire. On portera une attention
particulière aux valeurs de retours des fonctions de la libc
utilisées.

Ensuite, il va falloir implémenter un programme qui affiche la
position dans le tableau de l'élément de valeur 42. Vous ferez en
sorte d'exécuter le moins de tours de boucle possibles.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/bingo/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* générer des nombres aléatoires? `man srand` ; `man rand` ;
* sortir d'une boucle en cours d'exécution? `break`
* afficher un message d'erreur explicite en cas d'erreur dans une
  fonction de la libc? `man perror`

</details>

# Compétences

* Affichage formaté sur la sortie standard
* Condition simple if
* Boucles for
* break, continue
* Allocation de mémoire dynamique type de donnée simple
* Gestion d'erreurs à base de perror

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: bingo

.PHONY: clean
clean:
	rm -f *~ *.o bingo

```

#### Corrigé du fichier bingo.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

/* Alloue et initialise un tableau contenant la suite des entiers
 * naturels strictement positifs de l'intervalle [1; val_max] rangés à
 * des positions aléatoires. */
static uint32_t *generer_tab_aleatoire(uint32_t val_max)
{
    uint32_t *tab = NULL;
    tab = calloc(val_max, sizeof(uint32_t));
    if (tab == NULL) {
        perror("[bingo.c] Allocation du tableau");
        exit(EXIT_FAILURE);
    }
    /* Initialisation du générateur de nombres aléatoires. A chaque
     * seconde, la graine change. */
    srand(time(NULL));

    for (uint32_t i = 1; i <= val_max; i++) {
        uint32_t pos;
        do {
            pos = rand() % val_max;
        } while(tab[pos] != 0);
        tab[pos] = i;
    }

    return tab;
}

int main(void)
{
    uint32_t val = 42;
    uint32_t *tab = generer_tab_aleatoire(512);

    /* A compléter */
    for (uint32_t i = 0; i < 512; i++) {
        if (tab[i] == val) {
            printf("%u est en position %u.\n", val, i);
            /* break permet de sortir de la boucle (mais pas de la
             * fonction englobante (return) ni du programme
             * (exit)! */
            break;
        }
    }
    /* Si on avait exécuté return à la place de break ci-dessus, on
     * n'aurait pas pu atteindre cette ligne. */
    /* Consigne: cette ligne doit rester la dernière du programme. */
    free(tab);

    return EXIT_SUCCESS;
}

```


</details>
