# Énoncé

Chez les papous,

* y'a des papous papa à poux
* y'a des papous papa pas à poux
* y'a des papous pas papa à poux
* y'a des papous pas papa pas à poux

Et chez les pas papous, y'a une fonction `afficher_papous` qu'il faut
implémenter en utilisant des conditionnelles et des opérateurs
logiques.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/papous/`.

# Ressources associées

Besoin de plus d'infos sur les opérateurs booléens? Rendez-vous sur la fiche de cours [Opérateurs](http://formationc.pages.ensimag.fr/prepa/prof/papl/operateurs/).

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* AND s'écrit `&&` en C ;
* NOT s'écrit `!` en C.
</details>

# Compétences

* Opérateurs logiques
* Conditions if else
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

all: papous

.PHONY: clean
clean:
	rm -f *~ *.o papous

```

#### Corrigé du fichier papous.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void afficher_papous(bool est_papa, bool a_poux)
{
    printf("y'a des papous ");
    if (est_papa && a_poux) {
        printf("papa à poux\n");
    } else if (est_papa && !a_poux) {
        printf("papa pas à poux\n");
    } else if (!est_papa && a_poux) {
        printf("pas papa à poux\n");
    } else {
        printf("pas papa pas à poux\n");
    }

    /*
       On pouvait aussi tout afficher en une fois, en utilisant l'opérateur ternaire ?, qui s'utilise de cette façon :
       x = condition ? val_vrai : val_faux;
       et qui affecte la valeur val_vrai dans x si condition est vraie, et affecte val_faux sinon.
       (voir plus tard compétence avancée n°38)

       printf("y'a des papous %s papa %s à poux\n",
       est_papa ? "" : "pas",
       a_poux ? "" : "pas");
       */
}

int main(void)
{
    printf("Chez les papous...\n");
    afficher_papous(true, true);
    afficher_papous(true, false);
    afficher_papous(false, true);
    afficher_papous(false, false);

    return EXIT_SUCCESS;
}

```


</details>
