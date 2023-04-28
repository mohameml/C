# Énoncé

L'objectif de cet exercice est de manipuler une liste simplement
chaînée de cellules contenant un entier. Une liste sera ici
représentée par un pointeur vers sa première cellule, la tête de
liste.

On fournit ici la structure C représentant une cellule, la fonction principale (`main`) faisant quelques tests ainsi que les prototypes des fonctions à implémenter, à savoir :

1. L'insertion d'une valeur en tête de liste ;
2. L'insertion d'une valeur en queue de liste ;
3. La suppression d'une liste de la première occurrence d'une valeur
donnée ;
4. L'affichage des cellules d'une liste sur la sortie standard.

Le comportement attendu pour chaque fonction à implémenter est décrit
en commentaires au dessus de chacune d'entre elles.

*Remarque :* dans quel ordre écrire ces fonctions?

Il est important de compiler et tester au fur et à mesure que vous
développez, le plus tôt possible (et surtout pas tout coder avant
même d'essayer de compiler. Échec quasi-garanti).
Ici 1. permet de construire une liste et 4. de l'afficher. Avec ça,
vous aurez rapidement un programme certes incomplet mais qui fonctionne !
En plus vous réglerez d'éventuels problèmes de compréhension sur comment manipuler
les structures en jeu, et les fonctions suivantes seront beaucoup
plus simples à écrire.
(Cas contraire: imaginez que vous ayez écrit tout le code avec un couac
sur l'utilisation de la structure. Une fois le problème résolu, vous
devrez reprendre toutes les autres fonctions...)

Le point de départ pour cet exercice se trouve dans `exercices/base/listes/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Le mot-clé `NULL` désigne un pointeur nul. C'est pratique pour
  trouver la fin de ma liste.
* Ma tête de liste n'a pas été modifiée après un appel à
`inserer_tete` ?  Ca ne vous rappelle pas `echanger_faux` vu dans la
fiche de cours [Pointeurs](http://formationc.pages.ensimag.fr/prepa/prof/papl/pointeurs/) ?
</details>

# Compétences

* Structures
* Passage de paramètre par copie
* Passage de la valeur d'une variable
* Passage de l'adresse d'une variable
* Opérateur adresse de
* Opérateur d'indirection
* Fonction taille mémoire d'un type de donnée
* Allocation de mémoire dynamique type de donnée simple
* Libération de mémoire
* Pointeurs de structures
* Listes chainées

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: listes

.PHONY: clean
clean:
	rm -f *~ *.o listes
	rm -rf *.dSYM # mac-erie

```

#### Corrigé du fichier listes.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>

/**
 * @brief Structure de données décrivant un élément d'une liste.
 *
 */
struct cellule
{
    uint32_t val;           /**< La valeur d'une cellule est un entier */
    struct cellule* suiv;   /**< Pointeur vers la cellule suivant dans la liste */
};

/**
 * @brief Affiche sur la sortie standard les valeurs des cellules d'une liste.
 *
 * @param l la liste à afficher
 */
static void afficher(struct cellule* l)
{
    /* A implémenter! */
    while (l != NULL) {
        printf("%i -> ", l->val);
        l = l->suiv;
    }
    printf("FIN\n");
}

/**
 * @brief Insère une nouvelle cellule en tête d'une liste.
 *
 * @param pl l'adresse de la tête de la liste à étendre
 * @param v la valeur de la nouvelle cellule à créer et insérer
 */
static void inserer_tete(struct cellule** pl, uint32_t v)
{
    /* A implémenter! */
    /*
        Rappel : une liste est définie comme un pointeur vers la première
        cellule.  Comme cette fonction modifie la liste (la première cellule),
        la fonction appelante doit passer l'adresse de la liste pour pouvoir
        observer les changements (cf fiche passage de paramètres du kit de
        démarrage). Ainsi pl contient l'adresse de la liste et *pl désigne la
        liste (cad l'adresse de la première cellule).
    */

    /*
        On alloue une nouvelle cellule, qui sera la tête de la nouvelle liste.
        L'opérateur sizeof calcule le nombre d'octet à allouer pour le type
        voulu.
    */
    struct cellule* liste = malloc(sizeof(struct cellule));
    /*Programmation défensive : on vérification que malloc s'est bien passé*/
    assert(liste != NULL);
    /* On fixe les valeurs de cette cellule. */
    liste->val = v;
    liste->suiv = *pl;
    /* On fait pointer l'argument pl vers la nouvelle liste */
    *pl = liste;
}

/**
 * @brief Insère une nouvelle cellule en dernière position d'une liste.
 *
 * @param pl l'adresse de la tête de la liste à étendre
 * @param v la valeur de la nouvelle cellule à créer et insérer
 */
static void inserer_queue(struct cellule** pl, uint32_t v)
{
    /* A implémenter! */
    /*
        Cette fonction prend en argument un pointeur sur la liste, car cette
        dernière change dans le cas de l'insertion de la première cellule.

        On place une sentinelle de manière à gérer à l'identique tous les cas
        incluant le cas liste vide. Le champ suiv de notre sentinelle sera la
        liste que l'on voudra retourner.
    */
    struct cellule sent = { -1, *pl };
    struct cellule* queue = &sent;
    /* On parcourt la liste jusqu'à la dernière cellule */
    while (queue->suiv != NULL) {
        queue = queue->suiv;
    }
    /* Allocation et insertion de la cellule */
    queue->suiv = malloc(sizeof(struct cellule));
    assert(queue->suiv != NULL);
    queue->suiv->val = v;
    queue->suiv->suiv = NULL;
    /* On fait pointer l'argument pl vers la nouvelle liste */
    *pl = sent.suiv;
}

/**
 * @brief Supprime la première occurrence d'une valeur dans une liste.
 *
 * @param pl l'adresse de la tête de la liste sur laquelle appliquer la suppression
 * @param v la valeur que l'on souhaite supprimer de la liste
 */
static void supprimer_premiere_occurrence(struct cellule** pl, uint32_t v)
{
    /* A implémenter! */
    /*
        Cette fonction prend en argument un pointeur sur la liste, car cette
        dernière change lorsqu'on supprime la première cellule.
    */
    struct cellule sent = { -1, *pl };
    struct cellule* p = &sent;
    /*
        En C, les conditions sont évaluées séquentiellement. L'expression à
        droite d'une condition logique && n'est évaluée que si l'expression à
        gauche est vraie.
    */
    while (p->suiv != NULL && p->suiv->val != v) {
        p = p->suiv;
    }

    /* Cas occurence trouvée */
    if (p->suiv != NULL) {
        /*
            On rechaine les 2 cellules de la liste entourant l'occurrence et on
            libère la cellule trouvée.
        */
        struct cellule* style = p->suiv;
        p->suiv = style->suiv;
        free(style);
    }
    *pl = sent.suiv;
}

/**
 * @brief Point d'entrée du programme.
 *
 * @return int 0 (EXIT_SUCCESS) si tout s'est bien passé
 */
int main(void)
{
    struct cellule* liste = NULL;
    for (uint32_t i = 6; i < 10; i++) {
        inserer_queue(&liste, i);
        afficher(liste);
    }
    for (uint32_t i = 5; i > 0; i--) {
        inserer_tete(&liste, i);
        afficher(liste);
    }

    /*
        Initialisation du générateur de nombres aléatoires
        (nécessaire pour que rand() retourne des valeurs différentes à chaque
        exécution du programme).
    */
    srand(time(NULL));

    while (liste != NULL) {
        supprimer_premiere_occurrence(&liste, rand() % 10);
        afficher(liste);
    }
    return EXIT_SUCCESS;
}

```


</details>
