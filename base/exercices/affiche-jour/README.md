# Énoncé

L'objectif de cet exercice est de manipuler un type
énuméré. L'utilisateur appellera ce programme avec un entier en
argument sur la ligne de commande. Cet entier représente un jour de
la semaine: 1 pour lundi, 2 pour mardi, etc. On vous demande de
compléter ce programme de telle sorte que :

  - la chaîne de caractères `"Le nombre entré correspond à un jour de
  semaine."` soit affichée si le nombre passé en argument du programme
  est compris entre 1 et 5 (lundi au vendredi) ;

  - la chaîne de caractères `"Le nombre entré correspond à un jour du
  week-end."` soit affichée si le nombre passé en argument du programme
  est 6 ou 7 (samedi ou dimanche) ;

  - la chaîne de caractères `"Le nombre entré doit être compris entre 1
  et 7!"` soit affichée si le nombre passé en argument du programme
  n'est pas compris entre 1 et 7.

On utilisera un type énuméré pour représenter les jours de la
semaine, et une construction switch pour énumérer les valeurs
possibles prises par l'entier `nombre` déclaré dans le main.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/affiche-jour/`.

# Ressources associées

Pour tous les nintendophiles (et les autres), on parle de switch dans la fiche [Structures de contrôle](http://formationc.pages.ensimag.fr/prepa/prof/kit/ctrl/).

On parle des types énumérés dans la fiche de cours [Types énumérés](http://formationc.pages.ensimag.fr/prepa/prof/papl/enum).

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* `enum` permet de déclarer un type énuméré (voir section 6.14 du poly,
  page 128) ;
* la syntaxe du `switch` est détaillée en section 3.15.1 page 57 du
  poly.

</details>

# Compétences

* Enumérations
* Conditions de type switch

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: affiche-jour

.PHONY: clean check

check:
	make -C tests/ check

clean:
	rm -f *~ *.o affiche-jour

```

#### Corrigé du fichier affiche-jour.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

enum jour
{
    lundi = 1,
    mardi,
    mercredi,
    jeudi,
    vendredi,
    samedi,
    dimanche
};
int main(int argc, char **argv)
{
    /* Affiche un message d'erreur si l'utilisateur oublie l'argument
     * à passer en ligne de commandes. */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s nombre\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Convertit l'argument passé par l'utilisateur en entier. */
    int32_t nombre = atoi(argv[1]);

    /* On énumère les valeurs possibles prises par la variable
     * nombre: */
    switch(nombre) {
        case lundi:
        case mardi:
        case mercredi:
        case jeudi:
        case vendredi:
            /* Notez l’enchaînement de constructions 'case' ici: cela
             * signifie qu'on effectue la même opération si la valeur de
             * 'nombre' est égale à lundi, mardi, mercredi, jeudi ou
             * vendredi. */
            printf("Le nombre entré correspond à un jour de semaine.\n");
            /* break permet de sortir du switch. */
            break;
        case samedi:
        case dimanche:
            /* Même astuce pour samedi et dimanche. */
            printf("Le nombre entré correspond à un jour du week-end.\n");
            break;
        default:
            /* On tombe ici si la valeur de 'nombre' ne correspond à
             * aucun des cas énumérés ci-dessus. */
            printf("Le nombre entré doit être compris entre 1 et 7!\n");
            /* Pas besoin de break ici, puisqu'on sort du switch tout de
             * suite après. */
    }
    return EXIT_SUCCESS;
}

```


</details>
