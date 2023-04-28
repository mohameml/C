# Énoncé

Cet exercice illustre le mécanisme de passage de paramètres à une fonction C.

L'objectif est d'écrire des fonctions qui doivent modifier une donnée en paramètre (un entier, un pointeur et le contenu d'un tableau).

Le point de départ pour cet exercice (squelette de code, énoncé) se trouve dans `exercices/base/param/`.

# Ressources associées

On parle de passage de paramètres dans la fiche [Pointeurs](https://formationc.pages.ensimag.fr/prepa/prof/papl/pointeurs/).

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
Relisez bien l'exemple donné dans la fiche Pointeurs sur le passage de paramètres en C (fonction `echange_faux` versus `echange`).
<br>

</details>

# Compétences

* Opérateur adresse de
* Opérateur d'indirection
* Passage de paramètre par copie
* Passage de la valeur d'une variable
* Passage de l'adresse d'une variable

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier param.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/*
    A insérer ici les implémentations des fonctions :
    - void incremente(...) qui doit incrémenter la valeur d'un entier
      récupéré par l'intermédiaire d'un paramètre ;
    - void met_a_zero(..., size_t len) qui doit mettre les len cases
      du tableau récupéré par l'intermédiaire d'un paramètre à 0 ;
    - void met_a_null(...) qui passe le pointeur récupéré par l'intermédiaire
      d'un paramètre à la valeur NULL.

    Les ... dans les prototypes détaillés ci-dessus sont à remplacer par ce qui
    vous semble adéquat.
*/

/*
    On déclare ces trois fonctions static, puisqu'elles ne seront utilisées que
    dans ce fichier.
*/
/*
    On passe l'adresse de l'entier dont on veut modifier la valeur.
    La variable x est locale à la fonction incremente, et a été
    initialisée à l'entrée de la fonction à la valeur passée en paramètre
    d'incremente(), dans le main. Autrement dit, quand on entre dans la fonction
    incremente(), x vaut &toto, ou encore x référence toto.
*/
static void incremente(int8_t* x)
{
    /*
        On utilise l'opérateur * pour aller lire et écrire la valeur
        référencée par x (donc celle de la variable toto ici).
    */
    *x = *x + 1;
}

/*
    En C, un tableau est représenté par l'adresse de son premier élément.
    On passe donc l'adresse du premier élément du tableau à modifier
    en parametre de met_a_zero.

    Là encore, la variable tab est locale à la fonction met_a_zero, et
    a été initialisée à l'entrée de la fonction à la valeur passée en
    paramètre de met_a_zero() dans le main. Autrement dit, tab vaut pouet
    à l'entrée de la fonction, c'est-à-dire que comme pouet, tab référence
    le premier élément du tableau pouet.
*/
static void met_a_zero(int8_t* tab, size_t len)
{
    for (size_t i = 0; i < len; i++)
        tab[i] = 0;
    /*
        tab[i] est équivalent à *(tab + i).
        On parcourt donc les len éléments accessibles depuis l'adresse
        portée par la variable tab, et on les met tous à 0.
    */
}

/*
    Ici on cherche à modifier la valeur d'un pointeur passé en paramètre.
    Comme pour incremente(), on va passer l'adresse de cette variable pour
    pouvoir en modifier le contenu à l'intérieur de la fonction met_a_null().

    La variable ptr est locale à la fonction met_a_null, et a été
    initialisée à l'entrée de la fonction à la valeur passée en paramètre
    de met_a_null(), dans le main. Autrement dit, quand on entre dans la fonction
    met_a_null(), ptr vaut &coucou, ou encore ptr référence coucou.
*/
static void met_a_null(char** ptr)
{
    /*
        On utilise l'opérateur * pour aller écrire la valeur
        référencée par ptr (donc celle de la variable coucou ici).
    */
    *ptr = NULL;
}

int main(void)
{
    int8_t toto = 0;
    // TODO : insérez ici un appel à la fonction incremente pour modifier la valeur de toto
    incremente(&toto);
    assert(toto == 1);

    int8_t pouet[] = { 1, 2, 3 };
    // TODO : insérer ici un appel à la fonction met_a_zero pour mettre toutes les cases de pouet à 0
    met_a_zero(pouet, 3);
    assert(pouet[0] == 0 && pouet[1] == 0 && pouet[2] == 0);

    char* coucou = "hello !";
    // TODO : insérer ici un appel à la fonction met_a_null pour mettre coucou à NULL
    met_a_null(&coucou);
    assert(coucou == NULL);

    printf("Bravo, si vous arrivez jusqu'ici, c'est que tout fonctionne bien !\n");

    return EXIT_SUCCESS;
}

```


</details>
