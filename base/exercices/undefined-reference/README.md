# Enoncé

L'objectif de cet exercice est de compiler à la main (c'est-à-dire
sans utiliser de `Makefile`) un programme C qui fait appel à une
bibliothèque externe.

Une fois cette prouesse accomplie, on vous demande aussi d'écrire un
`Makefile` qui automatise la génération de l'exécutable `compile-toi`.

Attention, les deux solutions doivent être abordées et comprises
(compilation à la main + `Makefile`).

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/undefined-reference/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* man sqrt doit vous aider à comprendre comment compiler un programme
faisant appel à la fonction 'sqrt'

</details>

# Compétences

* Edition de liens
* Lien avec librairies standard C
* Makefile simple

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier compile-toi.c

```c
/*
    Enoncé :

    L'objectif de cet exercice est de compiler à la main
    (c'est-à-dire sans utiliser de Makefile) un programme C qui fait
    appel à une bibliothèque externe.

    Une fois cette prouesse accomplie, on vous demande aussi d'écrire
    un Makefile qui automatise la génération de l'exécutable
    compile-toi.

    Attention, les deux solutions doivent être abordées et comprises
    (compilation à la main + Makefile).

 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    /*
        Si on compile ce programme à l'aide de la commande:

            gcc -Wall -Wextra -std=c99 compile-toi.c -o compile-toi

        alors on obtient un message d'erreur de ce type:

            compile-toi.c:(.text+0x24): undefined reference to `sqrt'

        En effet, le compilateur indique qu'au moment de l'édition de
        liens, il n'a pas été capable de retrouver l'implémentation de
        la fonction 'sqrt'. Celle-ci se trouve dans la bibliothèque
        libm (voir 'man sqrt'). On doit donc rajouter cette
        bibliothèque à la ligne de compilation:

            gcc -Wall -Wextra -std=c99 compile-toi.c -o compile-toi -lm
    */
    printf("La racine carrée de 427 est %g.\n", sqrt(427));
    return EXIT_SUCCESS;
}

/*
    Makefile v1 : On fait exactement ce qu'on faisait en ligne de
    commande, à ceci près qu'on utilise les variables CC, CFLAGS,
    LDFLAGS, qui permettent de rapidement modifier les options de
    compilation, le compilateur utilisé, etc. On peut même facilement
    surcharger leur contenu en ligne de commande. Par exemple, make
    CC=clang effectuera les mêmes opérations en remplaçant tous les appels
    à gcc par clang. Pratique!

    CC=gcc
    CFLAGS=-Wall -Wextra -std=c99 -g
    LDFLAGS=-lm

    all: compile-toi

    compile-toi: compile-toi.c
	   $(CC) $(CFLAGS) compile-toi.c -o compile-toi $(LDFLAGS)

    .PHONY: clean
    clean:
	   rm -rf compile-toi *.o *~


    Makefile v2 : On sépare génération des fichiers objets (.o) et
    construction de l'exécutable. C'est une pratique très courante, qui
    permet de ne recompiler que ce qui est nécessaire (les règles dont
    les dépendances ont été modifiées ou sont absentes). Ca ne sert à
    rien pour cet exemple qui ne compile qu'un fichier source, mais
    c'est vital pour la compilation de programmes composés de plusieurs
    fichiers source.

    CC=gcc
    CFLAGS=-Wall -Wextra -std=c99 -g
    LDFLAGS=-lm

    all: compile-toi

    compile-toi: compile-toi.o
        $(CC) compile-toi.o -o compile-toi $(LDFLAGS)

    compile-toi.o: compile-toi.c
        $(CC) -c $(CFLAGS) compile-toi.c

    .PHONY: clean
    clean:
	    rm -rf compile-toi *.o *~


    Makefile v3 : On utilise les règles implicites de make, qui par
    défaut va appeler $(CC) avec les options de compilation $(CFLAGS) et
    utiliser $(LDFLAGS) comme options à l'édition de liens.

    CC=gcc
    CFLAGS=-Wall -Wextra -std=c99 -g
    LDFLAGS=-lm

    all: compile-toi

    .PHONY: clean
    clean:
        rm -rf compile-toi *.o *~
*/

```


</details>
