# Énoncé

L'objectif de cet exercice est de compiler un programme C
qui fait appel à une fonction définie en dehors du programme
principal. Ce programme contient une erreur, qu'il faudra corriger
pour que la commande `make` produise un programme exécutable.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/implicit-declaration/`.

# Ressources associées

Sans vouloir spoiler, à la fin de la fiche [Compilation avancée : cycle de vie d'un programme C](https://formationc.pages.ensimag.fr/prepa/prof/papl/cycle2vie/), il se passe presque la même chose que dans cet exo.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* `man isupper` doit vous aider à comprendre comment compiler un programme
faisant appel à la fonction `isupper`

</details>

# Compétences

* Options warnings
* Préprocesseur (include)

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
# -Werror = les avertissements (warnings) deviennent des erreurs!
CFLAGS=-Wall -Wextra -Werror -std=c99

all: compile-moi

.PHONY: clean

clean:
	rm -f compile-moi.o compile-moi

```

#### Corrigé du fichier compile-moi.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    /*
        Si on compile ce programme à l'aide de la commande :

            make

        alors on obtient un message d'erreur de ce type :

            compile-moi.c:36:10: error: implicit declaration of function 'isupper' is invalid in C99

        En effet, le compilateur indique qu'au moment de la
        compilation du fichier compile-moi.c, il ne connait pas le
        prototype de la fonction isupper. Il ne peut donc pas vérifier
        que le programme l'utilise d'une façon syntaxiquement
        correcte, à savoir que la valeur de retour est traitée
        correctement et que les paramètres qui sont passés à 'isupper'
        sont du bon type. Le prototype de la fonction 'isupper' étant
        donné dans l'entête ctype.h (voir man isupper), il suffit de
        rajouter #include <ctype.h> pour que ce programme compile
        correctement.
    */
    char lettre = 'L';

    if (isupper(lettre)) {
        printf("La lettre %c est une majuscule.\n", lettre);
    } else {
        printf("La lettre %c est une minuscule.\n", lettre);
    }

    return EXIT_SUCCESS;
}

```


</details>
