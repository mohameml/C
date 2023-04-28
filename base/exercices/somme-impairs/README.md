# Énoncé

L'objectif de cet exercice est de calculer la somme des 5000 premiers
entiers impairs strictement positifs. On utilisera un tableau pour
stocker ces entiers, et on calculera ainsi la somme de ses
éléments. Vous devrez déclarer une constante `TAILLE_TAB` représentant
la taille du tableau.

On vous demande ici d'implémenter deux fonctions dans ce même fichier,
en plus de la fonction `main` :

```c
void init_tab(uint32_t tab[], size_t length);
```

qui initialise le tableau passé en paramètre avec les valeurs des
`length` premiers entiers impairs strictement positifs.

```c
uint32_t somme_tab(uint32_t tab[], size_t length);
```
qui retourne la somme des éléments du tableau `tab` passé en
paramètre.

Le résultat sera affiché sur la sortie standard.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/somme-impairs/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

Le mot-clé `const` permet de déclarer des constantes.

Lire éventuellement le chapitre 2 du poly traitant des tableaux.
</details>

# Compétences

* Tableaux statiques
* Notion de constante
* Boucles for
* Boucles while
* Découpage d'un module en fonctions
* Prototypes de fonctions

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: somme-impairs

.PHONY: clean
clean:
	rm -f *~ *.o somme-impairs

```

#### Corrigé du fichier somme-impairs.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static void init_tab(uint32_t tab[], size_t length)
{
    for (uint32_t i = 0; i < length; i++) {
        tab[i] = 2*i + 1;
    }
}

static uint32_t somme_tab(uint32_t tab[], size_t length)
{
    uint32_t somme = 0;
    for (uint32_t i = 0; i < length; i++) {
        somme += tab[i];
    }
    return somme;
}


int main(void)
{
    /*
        La taille du tableau est ici une constante. Pour la déclarer, on
        utilise le mot-clé const. Pis 2 octets, ça suffit pour représenter
        la valeur 5000.
    */
    const uint16_t TAILLE_TAB = 5000;
    uint32_t somme = 0;
    /*
        Il n'existe pas de fonction de la libc ou de construction du langage
        permettant de compter les éléments d'un tableau quelconque. La taille du
        tableau est ici passée en paramètre des fonctions init_tab et somme_tab. Il
        n'est donc pas nécessaire de déclarer la constante TAILLE_TAB de manière
        globale, la déclarer dans le corps de la fonction main suffit.
    */
    uint32_t tab[TAILLE_TAB];

    init_tab(tab, TAILLE_TAB);
    somme = somme_tab(tab, TAILLE_TAB);

    printf("Somme des 5000 premiers entiers impairs strictement positifs = %u.\n", somme);

    return EXIT_SUCCESS;
}

```


</details>
