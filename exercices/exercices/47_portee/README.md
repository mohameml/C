# Enoncé

Voici un programme qui demande à l'utilisateur de saisir deux entiers
naturels au clavier représentant des coordonnées dans le plan. En
sortie, le programme affiche la distance entre le point saisi et
l'origine (0,0) du plan.

Seul hic, ce programme ne compile pas. Il y a en fait deux problèmes à
régler pour qu'il compile correctement :

```
	gcc -std=c99 -Wall -Wextra -g   -c -o portee.o portee.c
	portee.c:33:17: warning: implicit declaration of function 'distance_origine' is invalid in C99 [-Wimplicit-function-declaration]
	double d = distance_origine(p);
					  ^
	gcc -lm  portee.o point.o   -o portee
	duplicate symbol _afficher in:
	portee.o
	point.o
```

Le Makefile fourni est correct, c'est le code C de ce programme qu'il
faudra modifier pour faire disparaitre ces messages d'erreur.  En
revanche, il est interdit ici (sinon, c'est pas drôle), de renommer
les fonctions fournies.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/portee/`

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* jetez un oeil aux mot-clés "static" et "extern" dans le poly de C
</details>

# Compétences

* Options warnings
* Portée d'une fonction dans un module, un programme

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=-lm

all: portee

portee: portee.o point.o

.PHONY: clean
clean:
	rm -f *~ *.o portee

```

#### Corrigé du fichier portee.c

```c
#include <stdlib.h>
#include <stdio.h>

#include "point.h"

/*
    En rajoutant le mot-clé static, on limite la visibilité de la
    fonction afficher au fichier portee.c. En dehors de ce fichier, la
    fonction n'est pas visible. Elle n'entrera donc plus en conflit
    avec la fonction afficher définie dans point.c.
*/
static
void afficher(int argc, char **argv)
{
    for (int i = 0; i < argc; i++) {
        printf("argument %i: %s\n", i, argv[i]);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s coordX coordY\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Affichage pour du debug... */
    afficher(argc, argv);

    struct point p;
    p.x = atoi(argv[1]);
    p.y = atoi(argv[2]);

    double d = distance_origine(p);
    printf("Distance de ce point à l'origine: %lf.\n", d);

    return EXIT_SUCCESS;
}

```

#### Corrigé du fichier point.c

```c
#include <stdio.h>
#include <math.h>

#include "point.h"

/* Voir commentaires identiques dans portee.c. */
static
void afficher(struct point p)
{
    printf("(%u, %u)\n", p.x, p.y);
}

double distance_origine(struct point p)
{
    afficher(p);
    return sqrt(p.x*p.x + p.y*p.y);
}

```

#### Corrigé du fichier point.h

```c
#ifndef _POINT_H_
#define _POINT_H_

#include <stdint.h>

struct point {
    uint32_t x;
    uint32_t y;
};

/* On fournit le prototype de la fonction distance_origine pour
 * qu'elle puisse être utilisée à l'extérieur du module point, ce qui
 * corrige le problème "implicit declaration". */
extern double distance_origine(struct point p);

#endif /* _POINT_H_ */

```


</details>
