# Enoncé

Cet exercice vous met, l'espace d'un instant, dans la peau de Paul
le poulpe (https://fr.wikipedia.org/wiki/Paul_le_poulpe).

L'objectif est de pronostiquer les résultats du groupe A de
l'EURO2016 de foot (si vous n'en n'avez pas encore entendu parler,
c'est trop tard c'est déjà fini! Ben ouais, on recycle les exos des années
précédentes...).

Votre programme devra afficher les résultats du groupe A sous la
forme :

    Equipes	    V   D   N   bp  pc  diff    pts
    Albanie	    1   1   1   2   4   -2      4
    France 	    3   0   0   11  2   9       9
    Romania	    1   2   0   5   5   0       3
    Suisse 	    0   2   1   1   8   -7      1

Il vous est demandé de procéder de la manière suivante :

1- définir une structure de données struct equipe qui représente une équipe nationale, comprenant:
- son nom ;
- son nombre de victoires dans la phase de groupe (V) ;
- son nombre de défaites dans la phase de groupe (D) ;
- son nombre de matchs nuls (N) ;
- son nombre de buts marqués dans la phase de groupe (bp) ;
- son nombre de buts encaissés dans la phase de groupe (pc) ;
- la différence entre les buts marqués et les buts encaissés par cette
équipe (diff) ;
- le nombre de points de cette équipe (pts).

Le nombre de points est calculé de la manière suivante :
- 3 points pour une victoire ;
- 1 point pour un match nul ;
- 0 point pour une défaite.

2- définir le groupe A comme étant un tableau à 4 entrées, dont chaque entrée est une équipe (`struct equipe`).

La fonction main de votre programme devra déclarer le tableau
groupeA, l'initialiser de manière à ce qu'il représente les vraies
équipes de l'EURO (Albanie, France, Roumanie, Suisse), simuler le
résultat de chaque match et enfin afficher le tableau du groupe sous
la forme de ce qui est présenté plus haut.

Les équipes ne se rencontrent qu'une fois chacune. La simulation du
résultat d'un match sera implémentée dans la fonction :

```c
void jouer_match(struct equipe *e1, struct equipe *e2);
```

On utilisera un générateur de nombre aléatoire (fonction `rand()`)
pour simuler le nombre de buts marqués par chaque équipe dans un
match. On se ramènera à l'intervalle [0;5] pour être plus réaliste.
En fonction du nombre de buts marqués par chacune des deux équipes,
on pourra facilement mettre à jour les différents champs des
structures equipe e1 et e2.

Enfin, la fonction :

```c
void affiche_equipe(struct equipe *e);
```

affiche l'équipe passée en paramètre. Cet affichage correspond à
l'affichage d'une ligne du groupe, par exemple :

	France  3   0   0   11  2   9   9

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/euro2016/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

```c
struct pouet {
	int camion;
};

void toto(struct pouet *p) {
   	p->camion = 0;
}
```
modifie de manière pérenne la structure pointée par `p`.

```c
struct pouet tab[6];
```
déclare un tableau de 6 `struct pouet`.

```c
uint8_t val = rand() % 32;
```
tire un nombre aléatoire dans l'intervalle [0;31].

</details>

# Compétences

* Structures
* Opérateurs structures et unions
* Conditions if else
* Prototypes de structures de données
* Opérateur adresse de
* Pointeurs de structures

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: euro2016

.PHONY: clean
clean:
	rm -f *~ *.o euro2016

```

#### Corrigé du fichier euro2016.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

struct equipe;


/**
 * @brief Structure de données représentant une équipe.
 *
 */
struct equipe
{
    /*
        Le nom ici est juste un pointeur vers une chaine de
        caractères. Vous pouvez aussi déclarer une taille fixe de la
        forme char nom[TAILLE_NOM] et recopier le nom dans cette
        chaine.
    */
    char* nom;                  /**< Le nom de l'équipe */
    /*
        Pour le reste, on essaye d'utiliser les types les plus petits
        possibles.
    */
    uint8_t victoires;          /**< Le nombre de matchs gagnés par l'équipe */
    uint8_t defaites;           /**< Le nombre de matchs perdus par l'équipe */
    uint8_t nuls;               /**< Le nombre de matchs nuls concédés par l'équipe */
    uint8_t buts_marques;       /**< Le nombre de buts marqués par l'équipe */
    uint8_t buts_encaisses;     /**< Le nombre de buts encaissés par l'équipe */
    int8_t diff_buts;           /**< La différence entre buts marqués et buts encaissés par l'équipe */
    uint8_t points;             /**< Le nombre de points de l'équipe dans le classement */
};

/**
 * @brief Simule un match entre deux équipes passées en paramètre.
 *
 * Cette fonction simule un match entre deux équipes, en simulant
 * le nombre de buts marqués par chacun d'elle et en mettant à jour
 * les informations contenues dans chacune des struct equipe
 * associées à e1 et e2.
 *
 * @param e1 la première équipe
 * @param e2 la seconde équipe
 */
static void jouer_match(struct equipe* e1, struct equipe* e2)
{
    /* Tirage de nombre aléatoire dans l'intervalle [0;5] */
    uint8_t buts_marques_e1 = rand() % 6;
    uint8_t buts_marques_e2 = rand() % 6;

    e1->buts_marques += buts_marques_e1;
    e2->buts_marques += buts_marques_e2;

    e1->buts_encaisses += buts_marques_e2;
    e2->buts_encaisses += buts_marques_e1;

    /*
        Astuce: transtypé en entier, un booléen vaut 1 s'il est vrai
        et 0 sinon.
    */
    e1->victoires += (buts_marques_e1 > buts_marques_e2);
    e2->victoires += (buts_marques_e2 > buts_marques_e1);

    e1->defaites += (buts_marques_e1 < buts_marques_e2);
    e2->defaites += (buts_marques_e2 < buts_marques_e1);

    e1->nuls += (buts_marques_e1 == buts_marques_e2);
    e2->nuls += (buts_marques_e1 == buts_marques_e2);

    e1->diff_buts = e1->buts_marques - e1->buts_encaisses;
    e2->diff_buts = e2->buts_marques - e2->buts_encaisses;

    /* Pour maitriser la compétence 63! */
    if (buts_marques_e1 > buts_marques_e2) {
        e1->points += 3;
    } else if (buts_marques_e1 < buts_marques_e2) {
        e2->points += 3;
    } else {
        e1->points++;
        e2->points++;
    }
}

/**
 * @brief Affiche les statistiques de l'équipe passée en paramètre.
 *
 * @param e l'équipe dont on souhaite afficher les statistiques
 */
static void afficher_equipe(struct equipe* e)
{
    /* \t pour afficher une tabulation. */
    printf("%s\t%u\t%u\t%u\t%u\t%u\t%i\t%u\n",
        e->nom,
        e->victoires,
        e->defaites,
        e->nuls,
        e->buts_marques,
        e->buts_encaisses,
        e->diff_buts,
        e->points);
}

int main(void)
{
    /* Initialisation du générateur de nombres aléatoires, utilisé
     * dans jouer_match(). */
    srand(time(NULL));

    /*
        Initialisation contractée du tableau groupeA. Chaque case du
        tableau est en fait une struct equipe, qu'un initialise avec
        la notation { champ1, champ2, ..., champN }. Notez qu'on ne
        fait pas d'allocation dynamique pour les noms d'équipe. C'est
        un choix (et pas un bug), puisqu'on est sûrs ici que la chaine
        de caractères perdure jusqu'à la fin du programme (si vous ne
        comprenez pas cette dernière remarque, vous la comprendrez
        peut-être après avoir travaillé sur les pointeurs et
        l'allocation dynamique).
    */
    struct equipe groupeA[4] = {
        { "Albanie", 0, 0, 0, 0, 0, 0, 0 },
        { "France", 0, 0, 0, 0, 0, 0, 0 },
        /*
            Romania au lieu de Roumanie, pour ne pas avoir à
            s'embêter avec l'alignement des colonnes. Ouais, c'est
            petit, je sais.
        */
        { "Romania", 0, 0, 0, 0, 0, 0, 0 },
        { "Suisse", 0, 0, 0, 0, 0, 0, 0 }
    };

    /*
        On simule tous les matchs! Chaque équipe fait 3 matches au
        total.
    */
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = i + 1; j < 4; j++) {
            jouer_match(&groupeA[i], &groupeA[j]);
        }
    }

    /* On finit par l'affichage formaté des équipes. */
    printf("Equipe\tV\tD\tN\tbp\tpc\tdiff\tpts\n");
    for (uint8_t i = 0; i < 4; i++) {
        afficher_equipe(&groupeA[i]);
    }

    return EXIT_SUCCESS;
}

```


</details>
