# Enoncé

Cet exercice est un exercice de debug. Le programme suivant comporte
trois problèmes, à vous de les trouver en utilisant l'outil approprié,
puis de les corriger.

Ce programme permet de construire la suite croissante des `N` premiers
entiers `x` tels `x = 2^i`, pour i allant de 1 à N.

On utilise l'allocation dynamique pour allouer l'espace mémoire qui
permettra de stocker les termes de la suite, ce qui nous permet à
notre implémentation de gérer n'importe quelle taille de suite.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/suite/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* valgrind est un outil bien choisi pour traiter cet exercice.
</details>

# Compétences

* Structures
* Opérateurs de décalages binaires
* Opérateurs structures et unions
* Fonction taille mémoire d'un type de donnée
* Allocation de mémoire dynamique type de donnée simple
* Libération de mémoire
* Pointeurs de structures
* Utilisation de valgrind
* Gestion d'erreurs à base de perror

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: suite

.PHONY: clean
clean:
	rm -f *~ *.o suite

```

#### Corrigé du fichier suite.c

```c
/*
    Enoncé :

    Cet exercice est un exercice de debug. Le programme suivant comporte
    trois problèmes, à vous de les trouver en utilisant l'outil approprié,
    puis de les corriger.

    Ce programme permet de construire la suite croissante des N premiers
    entiers x tels x = 2^i, pour i allant de 1 à N.

    On utilise l'allocation dynamique pour allouer l'espace mémoire qui
    permettra de stocker les termes de la suite, ce qui nous permet à
    notre implémentation de gérer n'importe quelle taille de suite.

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/* La structure suite modélise notre suite de puissances de deux. */
struct suite
{
    /* Un tableau de puissances de deux. */
    uint32_t *terme;

    /* Le nombre de termes de la suite. */
    size_t taille;
};

/*
    Alloue et initialise une nouvelle suite dont la taille est passée
    en paramètre. La fonction retourne un pointeur sur la suite
    nouvellement crééé.
*/
static struct suite *init_suite(size_t taille)
{
    /*
        On souhaite créer un objet dont la durée de vie dépasse celle
        de la fonction init_suite. On utilise donc l'allocation
        dynamique : l'objet perdurera en mémoire tant qu'on n'aura pas
        explicitement libéré la mémoire qui lui est associé.
    */
    struct suite *ret = malloc(sizeof(struct suite));

    /*
        La ligne suivante indique : "Je suis certain que ret est
        différent de NULL!". Si ce n'est pas le cas, le programme
        s'arrête et un message explicite s'affiche sur le terminal
        (man assert). Si on voulait en savoir plus sur l'erreur qui
        s'est produite, on pourrait utiliser perror (man malloc, man
        perror).
    */
    assert(ret != NULL);

    ret->taille = taille;
    /*
        Même chose pour le tableau de termes : on souhaite qu'il soit
        toujours accessible quand cette fonction aura retourné.
    */
    ret->terme = malloc(taille * sizeof(uint32_t));
    assert(ret->terme != NULL);

    for (size_t i = 1; i <= taille; i++) {
        /*
            On construit la suite des taille premiers entiers x tels
            que x = 2^i.
        */
        ret->terme[i] = 1 << i;
        /*
           Un coup de valgrind sur ce programme renvoie:

           ==5695== Command: ./suite
           ==5695==
           ==5695== Invalid write of size 4
           ==5695==    at 0x4006C2: init_suite (suite.c:60)
           ==5695==    by 0x4005BD: main (suite.c:87)
           ==5695==  Address 0x4c390b8 is 0 bytes after a block of size 40 alloc'd
           ==5695==    at 0x4A06A2E: malloc (vg_replace_malloc.c:270)
           ==5695==    by 0x400652: init_suite (suite.c:54)
           ==5695==    by 0x4005BD: main (suite.c:87)
           ==5695==

           Autrement dit, on écrit 4 octets en dehors d'une zone
           mémoire allouée de taille 40 (4 octets * 10 éléments).  On
           reconnait ici notre tableau de termes. valgrind nous dit
           qu'on écrit 0 octets _après_ cette zone mémoire, donc
           qu'on essaye d'écrire dans terme[taille] alors qu'on n'a
           accès qu'aux cases terme[0] .. terme[taille-1] (les
           tableaux en C sont indexés à partir de 0).

           On peut donc corriger ce bug en changeant les bornes de la
           boucle for:

           for (size_t i = 0; i < taille; i++) {
           */
    }

    /*
        On retourne simplement l'adresse en mémoire où retrouver la
        suite allouée dynamiquement.
    */
    return ret;
}

/* Libère la mémoire allouée pour une suite. */
static void destroy_suite(struct suite *s)
{
    free(s->terme);
    free(s);
}

static void print_suite(struct suite *s)
{
    printf("La suite comporte %zu termes:\n", s->taille);
    for (size_t i = 1; i <= s->taille; i++) {
        /*
            Valgrind nous dit:

            ==5695== Invalid read of size 4
            ==5695==    at 0x400746: print_suite (suite.c:79)
            ==5695==    by 0x4005CA: main (suite.c:90)
            ==5695==  Address 0x4c390b8 is 0 bytes after a block of size 40 alloc'd
            ==5695==    at 0x4A06A2E: malloc (vg_replace_malloc.c:270)
            ==5695==    by 0x400652: init_suite (suite.c:54)
            ==5695==    by 0x4005BD: main (suite.c:87)
            ==5695==

            Si vous avez compris l'explication ci-dessus, ça devrait
            être limpide!
        */
        printf("%u ", s->terme[i]);
    }
    printf("\n");
}

int main(void)
{
    /* On créé une suite de 10 termes. */
    struct suite *s = init_suite(10);

    /* On l'affiche! */
    print_suite(s);
    /*
        Si on oublie de libérer la mémoire allouée par init_suite, on
        a une fuite mémoire! D'ailleurs, valgrind vous le dit :
            ==5935== LEAK SUMMARY:
            ==5935==    definitely lost: 16 bytes in 1 blocks
            ==5935==    indirectly lost: 40 bytes in 1 blocks
    */
    destroy_suite(s);

    return EXIT_SUCCESS;
}

```


</details>
