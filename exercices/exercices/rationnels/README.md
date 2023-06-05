# Énoncé

Dans cet exercice, vous allez manipuler des structures et vous
confronter aux problématiques liées au typage des variables en C.

On définit une structure rationnel contenant deux champs entiers, l'un
représentant son numérateur et l'autre son dénominateur.

On vous demande d'implémenter trois fonctions :

- `valeur_rationnel` qui retourne la valeur réelle du rationnel passé en paramètre, obtenue en divisant son numérateur par son dénominateur ;

- `somme_puis_convertit` qui calcule la somme des rationnels passés en
paramètres dans un nouveau rationnel, puis retourne la valeur réelle de ce nouveau rationnel ;

- `convertit_puis_somme` qui calcule d'abord la valeur réelle de
chacun des paramètres puis en calcule la somme.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/rationnels/`.

# Ressources associées

La fiche de cours [Pointeurs](http://formationc.pages.ensimag.fr/prepa/prof/papl/pointeurs/) illustre la manipulation de structures en C.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* un problème de division ? Allez lire la section 1.12.5 du poly (page 17)
* on accède au champ c d'une structure `s` via la syntaxe `s.c`
</details>

# Compétences

* Entiers
* Flottants
* Structures
* Transtypage de types simples
* Opérateurs arithmétiques

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: rationnels

.PHONY: clean
clean:
	rm -f *~ *.o rationnels

```

#### Corrigé du fichier rationnels.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/*
    On définit le type "struct rationnel" contenant deux champs:
    un numérateur et un dénominateur.
*/
struct rationnel
{
    /* numérateur */
    uint32_t n;

    /* dénominateur */
    uint32_t d;
};

/* Retourne la valeur réelle associée au rationnel r. */
static float valeur_rationnel(struct rationnel r)
{
    float ret;
    /*
        Le fait de convertir l'une des opérandes de la division en
        flottant oblige le compilateur à effectuer une division
        réelle. Si on ne fait pas ça, on effectue une division
        entière, puis on stocke le résultat (entier) de cette division
        dans un réel.
    */
    ret = (float)r.n / r.d;
    return ret;
}

/*
    Effectue la somme des rationnels r1 et r2 dans un nouveau rationnel
    r, puis retourne la valeur réelle qui lui est associée.
*/
static float somme_puis_convertit(struct rationnel r1,
                                  struct rationnel r2)
{
    float ret = 0.0;
    /*
        On utilise ici l'initialisation directe des champs de la
        structure rationnel. On aurait pu tout aussi bien déclarer r
        puis affecter ses différents champs de cette façon :

            struct rationnel r;
            r.n = r2.d * r1.n + r1.d * r2.n;
            r.d = r1.d * r2.d;
     */
    struct rationnel r = {
        r2.d * r1.n + r1.d * r2.n,
        r1.d * r2.d
    };
    ret = valeur_rationnel(r);
    return ret;
}

/*
    Retourne la somme des valeurs réelles associées aux rationnels r1
    et r2.
*/
static float convertit_puis_somme(struct rationnel r1,
                                  struct rationnel r2)
{
    float ret = 0.0;
    ret = valeur_rationnel(r1) + valeur_rationnel(r2);
    return ret;
}

int main(void)
{
    struct rationnel r1 = { 1, 7 };
    struct rationnel r2 = { 3, 4 };

    printf("%f est-il égal à %f?\n",
            somme_puis_convertit(r1, r2),
            convertit_puis_somme(r1, r2));

    return EXIT_SUCCESS;
}

```


</details>
