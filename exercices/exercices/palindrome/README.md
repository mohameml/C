# Énoncé

Un palindrome, ou "mot miroir", est un mot dont l'ordre
des lettres est le même qu'on le lise de droite à gauche ou de
gauche à droite. Par exemple, le prénom Anna est un
palindrome. Dans cet exercice, on vous demande d'implémenter la
fonction `est_palindrome`, qui renvoie vrai si le mot passé en
paramètre est un palindrome et faux sinon.
La fonction `main` fournie teste votre fonction `est_palindrome`.
On ne vous demande pas de comprendre ce qu'elle fait, sachez seulement que le
programme `./palindrome` prend en argument le mot sur lequel
travailler, par exemple:

```
./palindrome anna
anna est bien un palindrome!
```

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/palindrome/`.

# Ressources associées

Nous vous conseillons la lecture de la fiche de cours [Chaîne de caractères](http://formationc.pages.ensimag.fr/prepa/prof/papl/strings/) avant de traiter cet exercice.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* on a ici besoin de deux variables d'itérations, pour effectuer un
  parcours de gauche à droite et un parcours de droite à gauche ;
* la fonction `strlen` de la libc (`man strlen`) permet de connaître la taille d'une chaîne de caractères.
</details>

# Compétences

* Booléens
* Caractères
* Chaînes de caractères
* Traitement caractère par caractère
* Condition simple if
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

all: palindrome

.PHONY: clean
clean:
	rm -f *~ *.o palindrome

```

#### Corrigé du fichier palindrome.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static bool est_palindrome(const char *mot)
{
    size_t i = 0, j = strlen(mot) - 1;

    /*
        On itère sur les caractères de la chaîne mot de gauche à
        droite avec l'indice i et de droite à gauche avec l'indice
        j. Notez qu'il est possible de passer une série d'instructions
        à une boucle for si on les sépare par une virgule: ici, à
        chaque itération, on exécute i++ ET j--.
    */
    for (i = 0; i <= j; i++, j--) {
        if (mot[i] != mot[j]) {
            return false;
        }
    }
    return true;
}

/*
    Ce prototype de fonction main permet de récupérer les arguments
    passés au programme sur la ligne de commande (ici, le mot sur
    lequel travailler).
*/
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s mot\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (est_palindrome(argv[1])) {
        printf("%s est bien un palindrome!\n", argv[1]);
    } else {
        printf("%s n'est pas un palindrome...\n", argv[1]);
    }

    return EXIT_SUCCESS;
}

```


</details>
