# Énoncé

Cet exercice est une première application du contenu de la fiche [Pointeurs](https://formationc.pages.ensimag.fr/prepa/prof/papl/pointeurs/), où il vous sera demandé de déclarer et initialiser un pointeur, puis de le déréférencer pour afficher la valeur de la variable qu'il référence.

L'objectif est de modifier la valeur d'une variable par l'intermédiaire d'un pointeur.
Les consignes sont données en commentaires dans le code.

Le point de départ pour cet exercice (squelette de code, énoncé) se trouve dans `exercices/base/pointeurs/`.

# Ressources associées

La fiche [Pointeurs](https://formationc.pages.ensimag.fr/prepa/prof/papl/pointeurs/) vous apprendra tout ce qu'il y a à savoir sur... euh... les pointeurs.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
Go lire la fiche !
<br>

</details>

# Compétences

* Opérateur adresse de
* Opérateur d'indirection

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: pointeurs

.PHONY: clean
clean:
	rm -f *~ *.o pointeurs

```

#### Corrigé du fichier pointeurs.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    // Interdit de changer la ligne qui suit !
    uint8_t target = 123;

    /*
        Déclarer ci-dessous un pointeur appelé ptr
        et l'initialiser de manière à ce qu'il référence
        la variable target.
    */
    // TODO
    uint8_t* ptr = &target;

    /*
        Changer la valeur de target pour 255 par l'intermédiaire
        du pointeur ptr. Autrement dit, vous n'avez pas le droit
        ici d'écrire "target = 255;".
    */
    // TODO
    *ptr = 255;

    // Doit afficher "La valeur de target est 255."
    printf("La valeur de target est %u.\n", target);

    return EXIT_SUCCESS;
}
```


</details>
