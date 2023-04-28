# Enoncé

Cet exercice vous fera manipuler les opérateurs logiques.
Son but est d'exprimer dans la valeur de retour de la fonction noel
la condition d'un vrai Noël.
Un vrai Noël, c'est un Noël avec un sapin habillé de guirlandes et/ou
de boules et où personne ne pose de lapin.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/noel/`.

# Ressources associées

La fiche de cours [Opérateurs](http://formationc.pages.ensimag.fr/prepa/prof/papl/operateurs/) liste les opérateurs logiques disponibles en C.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Lire les pages 42 et 43 du poly (&&,||,!)
</details>

# Compétences

* Booléens
* Opérateurs logiques
* Conditions combinées avec opérateurs logiques

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: noel

.PHONY: clean
clean:
	rm -f *~ *.o noel

```

#### Corrigé du fichier noel.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static bool noel(bool boule, bool guirlande, bool sapin, bool lapin)
{
    // A compléter
    return  sapin && (guirlande || boule) && !lapin ;
}

int main(void)
{
    if ( noel(false,false,false,false)) goto Cestpasgagne;
    if ( noel(true ,false,false,false)) goto Cestpasgagne;
    if ( noel(false,true ,false,false)) goto Cestpasgagne;
    if ( noel(true ,true ,false,false)) goto Cestpasgagne;
    if ( noel(false,false,true ,false)) goto Cestpasgagne;
    if (!noel(true ,false,true ,false)) goto Cestpasgagne;
    if (!noel(false,true ,true ,false)) goto Cestpasgagne;
    if (!noel(true ,true ,true ,false)) goto Cestpasgagne;
    if ( noel(false,false,false,true )) goto Cestpasgagne;
    if ( noel(true ,false,false,true )) goto Cestpasgagne;
    if ( noel(false,true ,false,true )) goto Cestpasgagne;
    if ( noel(true ,true ,false,true )) goto Cestpasgagne;
    if ( noel(false,false,true ,true )) goto Cestpasgagne;
    if ( noel(true ,false,true ,true )) goto Cestpasgagne;
    if ( noel(false,true ,true ,true )) goto Cestpasgagne;
    if ( noel(true ,true ,true ,true )) goto Cestpasgagne;
    printf("Joyeux Noel\n");
    return EXIT_SUCCESS;
    /*
        Note : L'utilisation de goto en C est généralement à proscrire.
        Tracer des erreurs est une des rares exceptions à son usage.
    */

Cestpasgagne:
    printf("C'est pas gagné !\n");
    return EXIT_FAILURE;
}

```


</details>
