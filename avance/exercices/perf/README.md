# Enoncé

Cet exercice introduit le mécanisme de prise de temps en C pour
évaluer la performance de différentes implémentations du calcul de la
somme des 32 premières puissances de 2 (de 2^0 à 2^31 compris).

La bibliothèque standard C fournit, via la fonction `gettimeofday()`,
un mécanisme de prise de temps à la microseconde près. Pour évaluer le
temps pris par le calcul de la somme des 32 premières puissances de
deux, on fournit une fonction, `repeat_and_time()`, qui appelle un
certain nombre de fois une fonction passée en paramètre et affiche son
temps d'exécution moyen.

On vous demande donc ici d'implémenter la fonction de calcul de la
somme des 32 premières puissances de deux la plus efficace possible et
de la tester à l'aide de la fonction `repeat_and_time()`. Vous pourrez
ensuite comparer ses performances à celles des versions décrites dans
la correction de l'exercice.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/perf/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Pour calculer une puissance de 2, on peut utiliser le décalage
binaire, la fonction `pow()` de la libc, ... Si vous utilisez la
fonction `pow()`, assurez-vous d'abord qu'aucun prof d'archi ne lorgne
par dessus votre épaule!

</details>

# Compétences

* Opérateurs binaires
* Pointeurs de fonctions

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
# Cette ligne n'est utile que si votre programme
# utilise la lib maths (pour pow() par exemple).
LDFLAGS=-lm

all: perf

.PHONY: clean
clean:
	rm -f *~ *.o perf

```

#### Corrigé du fichier perf.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>

/*
    On décide de répéter l'exécution du bloc de code dont on veut mesurer
    le temps d'exécution un grand nombre de fois. Cela permet d'utiliser
    un outil de prise de temps à gros grain (comme gettimeofday(), qui compte
    à la granularité d'une microseconde) même quand on souhaite mesurer un
    traitement au temps d'exécution court (ici, de l'ordre de quelques nanosecondes
    pour certaines versions). Il suffira ensuite de diviser le temps obtenu
    par le nombre de répétitions pour obtenir une estimation du temps d'exécution
    du bloc de code étudié (représentant du coup la moyenne des temps obtenus).
*/
#define NTIMES 10000000

/*
    Le module de prise de temps définit une structure timeval, disposant de
    deux champs :
    - le nombre total de secondes écoulées tv_sec ;
    - le nombre de microsecondes écoulées depuis la dernière seconde tv_usec.

    Pour calculer le nombre total de microsecondes écoulées entre t1 et t2,
    on ramène le nombre de secondes en microsecondes en le multipliant
    par 1000000.
*/
static double elapsed_time(struct timeval t1,
                           struct timeval t2) {
    return (double)((t2.tv_sec - t1.tv_sec) * 1000000
           + (t2.tv_usec - t1.tv_usec));
}

/*
    Compte la somme des 32 premières puissances de deux à l'aide de la
    fonction pow(). Si un prof d'archi se trouve pas loin et que vous
    le voyez saigner du nez en voyant cette implémentation, c'est normal :
    c'est à peu près la pire façon de calculer une puissance de 2. La fonction
    pow() calcule n'importe quel nombre élevé à n'importe quelle puissance.
    En soit, elle n'est pas capable de détecter qu'on effectue en fait une
    élévation de 2 à la puissance i, et effectue donc cette opération à l'aide
    de multiplication sucessives. RIP, prof d'archi préféré :-(.
*/
static uint32_t compute_with_pow(void) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < 32; i++) {
        sum += pow(2, i);
    }
    return sum;
}

/*
    Compte la somme des 32 premières puissances de deux à l'aide de décalages.
    Cette version coûte beaucoup moins cher en matériel, puisque l'opération
    de décalage peut s'exécuter en un cycle. Votre prof d'archi reprend des
    couleurs, non?
*/
static uint32_t compute_with_shift(void) {
    uint64_t sum = 0;
    for (uint8_t i = 0; i < 32; i++) {
        sum += (1U << i);
    }
    return sum;
}

/*
    Certains d'entre vous l'auront peut-être remarqué : la somme des 32
    premières puissances de deux s'écrit en binaire comme une suite de
    32 bits positionnés à 1. On peut facilement générer cette valeur en
    prenant le complément à deux de 0, codé sur 32 bits. Et du coup, ben ça
    coûte plus grand chose. D'où l'intérêt de se poser les bonnes questions
    avant de foncer tête baissée dans l'implémentation de la version la plus
    évidente!
*/
static uint32_t compute_with_complement(void) {
    return ~((uint32_t)0);
}

/*
    On peut aussi remarquer qu'un ensemble de 32 bits à 1 équivaut à la valeur
    décimale -1, codée en complément à deux. Et là, pour le coup, on ne fait rien
    de plus que charger la valeur d'une constante.
*/
static uint32_t dont_compute_because_its_useless(void) {
    return (uint32_t)-1;
}

/*
    Cette fonction lance la fonction compute_sum passée en paramètre
    (et oui, un pointeur de fonction!) ntimes fois et affiche son temps
    d'exécution moyen, ainsi que la chaine de caractères version_tag.

    Un pointeur de fonction en C s'écrit de cette façon :
    type_de_retour (*nom_du_pointeur_de_fonction)(type_des_paramètres);

    Par exemple, char *(*camion)(void) représente une fonction sans
    paramètre, qui retourne une chaine de caractères. Je ne sais pas ce qu'elle
    fait, mais je sais que je peux l'appeler en écrivant :
    char *pouetpouet = camion();

    Pour passer une fonction en paramètre d'une autre fonction, on utilise
    simplement son nom :
    repeat_and_time(hello, 10, "blabla");
    compilera à condition que hello soit une fonction de prototype :
    uint32_t hello(void);
*/
static void repeat_and_time(uint32_t (*compute_sum)(void),
                            uint32_t ntimes,
                            const char *version_tag) {
    struct timeval start, stop;
    /*
        Un appel à gettimeofday remplit la structure timeval passée en
        paramètre avec le nombre de secondes et de microsecondes
        écoulées depuis une certaine date (par défaut le 1er janvier 1970).
    */
    gettimeofday(&start, NULL);
    uint32_t sum = 0;
    for (unsigned times = 0; times < ntimes; times++) {
        sum = compute_sum();
    }
    gettimeofday(&stop, NULL);
    printf("Elapsed time for %s: %lfus\n",
            version_tag,
            elapsed_time(start, stop) / NTIMES);
    assert(sum == (uint32_t)-1);
}

int main(void)
{
    /*
        TODO: Définir une fonction qui calcule la somme des 32 premières
        puissances de 2 et l'évaluer à l'aide de repeat_and_time().
    */
    repeat_and_time(compute_with_pow, NTIMES, "pow version");
    repeat_and_time(compute_with_shift, NTIMES, "shift version");
    repeat_and_time(compute_with_complement, NTIMES, "complement version");
    repeat_and_time(dont_compute_because_its_useless, NTIMES, "Mumu's version");

    return EXIT_SUCCESS;
}

```


</details>
