# Énoncé

Cet exercice vous fera travailler les boucles. Vous devez
implémenter un programme itératif qui demande à l'utilisateur
d'entrer une majuscule au clavier. Si l'utilisateur entre autre
chose qu'une majuscule, le programme réitère sa demande jusqu'à
obtenir une majuscule. Dès que l'utilisateur entre une majuscule, le
programme affiche cette majuscule et s'arrête.

Vous pourrez utiliser la fonction `isupper` de la libc (`man isupper`
pour plus d'informations sur cette fonction).

On utilisera une boucle `do ... while` comme boucle principale du
programme.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/do-while/`.

# Ressources associées

La construction d'une boucle `do ... while` est décrite dans le [poly](http://formationc.pages.ensimag.fr/prepa/prof/docs/poly-c.pdf), section 2.2.3 page 39.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* `getc` permet de récupérer un caractère entré au clavier (`man
  getc`) ;
* `isupper` permet de tester si un caractère est une majuscule (`man
  isupper`) ;
* quand l'utilisateur entre un caractère au clavier, il valide son
  choix en appuyant sur la touche entrée. Ça fait donc deux caractères
  présents sur l'entrée standard : le caractère de l'utilisateur et le
  caractère spécial de retour à la ligne. Faites attention à ce que
  votre programme ne traite pas ce caractère supplémentaire.

</details>

# Compétences

* Caractères
* Traitement caractère par caractère
* Boucles do while

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: do-while

.PHONY: clean
clean:
	rm -f *~ *.o do-while

```

#### Corrigé du fichier do-while.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>     // pour isupper

int main(void)
{
    char maj;

    do {
        /*
            À la différence d'une boucle while, do ... while
            garantit qu'on entre au moins une fois dans le corps de
            la boucle. On évite ainsi d'initialiser la variable maj à
            une valeur particulière, puisqu'elle sera forcément
            affectée avant le test isupper(maj).
        */
        printf("Entrez une majuscule : ");

        /* On récupère un caractère au clavier. */
        maj = getc(stdin);

        /*
            Quand on entre un caractère au clavier, on en tape en
            fait deux: le caractère en question, puis le caractère
            'entrée' pour valider notre choix. Ce caractère
            supplémentaire est placé dans une mémoire tampon, en
            attendant d'être lu par un prochain appel à getc par
            exemple. Ce caractère ne doit pas être traité par notre
            boucle principale, c'est pourquoi on vide explicitement
            la mémoire tampon associée à l'entrée standard par un
            appel à getc jusqu'à tomber sur le caractère de retour
            a la ligne '\n'.
            La boucle ci-dessous permet également de gérer le cas ou
            l'utilisateur entre plusieurs caractères au clavier avant
            d'appuyer sur 'entrée'
         */
        char nl;
        do {
            nl = getc(stdin);
        } while (nl != '\n');

        /* On s'arrête dès que le caractère est une majuscule. */
    } while (!isupper(maj));

    printf("Votre majuscule : %c\n", maj);

    return EXIT_SUCCESS;
}

```


</details>
