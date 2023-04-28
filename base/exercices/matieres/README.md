# Enoncé

Dans cet exercice, on manipule directement les bits d'un entier.  On
modélise l'ensemble des matières d'un élève du secondaire sous la
forme d'un entier 8 bits. On associe à chaque matière une position
différente dans cet octet, que l'on interprête de cette façon :

_Si le k-ième bit de l'octet est à 1, c'est que l'élève maitrise la
matière correspondante ; sinon, c'est qu'il n'a rien compris à cette
matière._

On vous demande d'implémenter dans un premier temps les fonctions
de manipulation des ensembles codés sur un octet, à savoir :

- `u8_set_bit(pos, u, val)` qui affecte la valeur `val` au "pos-ième"
bit de `u` ;

- `u8_bit_is_set(pos, u)` qui renvoie vrai si le "pos-ième" bit de `u`
vaut 1 et faux s'il vaut 0.

Vous utiliserez ensuite ces deux fonctions pour implémenter la
fonction `evaluer_eleve()` qui, étant donné un ensemble de matières
produit un affichage indiquant quelles sont celles qui ont été
maitrisées par l'élève et quelles sont celles qui n'ont pas été
comprises.

Enfin, toujours en s'appuyant sur les fonctions de manipulation des
ensembles définies précédemment, vous implémenterez la fonction
`passer_examen()` qui, étant donné un ensemble de matières
représentant les épreuves d'un examen, met à jour les compétences
d'un élève en fonction de la réussite ou de l'échec à chaque
épreuve.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/matieres/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Vous trouverez une description des opérateurs bit-à-bit du langage C en section 7.2 du poly (page 127).
</details>

# Compétences

* Booléens
* Enumérations
* Définition de type
* Opérateurs binaires
* Opérateurs de décalages binaires

# Difficulté

:star: :star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: matieres

.PHONY: clean
clean:
	rm -f *~ *.o matieres

```

#### Corrigé du fichier matieres.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

/*
    On définit un nouveau type pour représenter l'ensemble des
    compétences d'un élève. Manipuler un skill_set_t revient à
    manipuler un entier non-signé codé sur 8 bits, mais le fait de
    définir un type ici améliore la lisibilité du code : quand on
    définit une variable de type skill_set_t, on comprend qu'on fait
    spécifiquement référence à un ensemble de compétences. */
typedef uint8_t skill_set_t;

/* Même chose pour un examen: c'est un ensemble de matières. */
typedef uint8_t exam_t;

/*
    On définit une constante pour chaque matière, dont la valeur
    correspond à sa position dans l'octet représentant un ensemble.
*/
enum course_id
{
    MATHS = 0,
    PHYSIQUE,
    CHIMIE,
    FRANCAIS,
    HISTOIRE,
    GEO,
    PHILO,
    SPORT,
    NB_MATIERES /* Astuce répandue pour récupérer facilement le
                 * nombre d'éléments d'un type énuméré. */
};

/*
    Noms des matières rangés dans le même ordre que les éléments du type
    énuméré course_id, pour affichage.
*/
static const char *course_name[NB_MATIERES] = {
    "maths",
    "physique",
    "chimie",
    "francais",
    "histoire",
    "geo",
    "philo",
    "sport"
};

/*
    Renvoie true si le bit en position pos prend la valeur 1 dans
    l'octet u, false sinon.
*/
static bool u8_bit_is_set(uint8_t pos, uint8_t u)
{
    bool ret = false;
    ret = (u & (1 << pos)) != 0;
    return ret;
}

/*
    Change la valeur du bit en position pos dans l'octet u, pour lui
    donner la valeur 1 si val vaut true et 0 sinon. La fonction
    retourne l'octet modifié.
*/
static uint8_t u8_set_bit(uint8_t pos, uint8_t u, bool val)
{
    uint8_t ret = 0;
    ret = val ? (u | (1 << pos)) : (u & ~(1 << pos));
    return ret;
}

/*
    Parcourt l'ensemble s passé en paramètre et produit un affichage de
    la forme :

        Paul est nul en maths!
        Paul est nul en physique!
        Paul est nul en chimie!
        Paul est bon en francais!
        Paul est bon en histoire!
        Paul est nul en geo!
        Paul est bon en philo!
        Paul est nul en sport!

    où Paul est nom de l'élève contenu dans le paramètre nom, ou :

        Wow, Paul maitrise tout!

    si l'élève évalué maitrise toutes les matières.
*/
static void evaluer_eleve(const char *nom, skill_set_t s)
{
    skill_set_t champion = ~0;
    if (s == champion) {
        printf("Wow, %s maitrise tout!\n", nom);
    } else {
        for (uint8_t i = 0; i < NB_MATIERES; i++) {
            printf("%s est %s en %s!\n",
                    nom,
                    u8_bit_is_set(i, s) ? "bon" : "nul",
                    course_name[i]);
        }
    }
}

/*
    Fait passer un examen à un étudiant dont les compétences sont
    représentées par le paramètre s.

    En pratique, exam est l'ensemble des épreuves (matières) composant
    l'examen à passer. Pour se rapprocher de la vraie vie, on tirera un
    nombre aléatoire pour modéliser la réussite ou l'échec à une
    épreuve : si ce nombre est impair, l'épreuve est réussie, sinon,
    l'épreuve est échouée.

    Cette fonction renvoie une nouvelle version des compétences de
    l'élève, mise à jour en fonction de la réussite ou de l'échec des
    épreuves de l'examen passé en paramètre.
 */
static skill_set_t passer_examen(exam_t exam, skill_set_t s)
{
    skill_set_t ret = 0;
    ret = s;
    for (uint8_t i = 0; i < NB_MATIERES; i++) {
        if (u8_bit_is_set(i, exam)) {
            bool success = rand()&1;
            ret = u8_set_bit(i, ret, success);
        }
    }
    return ret;
}


int main(void)
{
    /*
        Initialisation du générateur de nombres aléatoires nécessaire
        pour implémenter passer_examen (voir man 3 rand).
    */
    srand(time(NULL));

    skill_set_t s = 0;

    /*
        Hypothèses douteuses : les littéraires sont nuls en maths, en
        physique, en chimie et en sport...
    */
    s = u8_set_bit(FRANCAIS, s, true)
        | u8_set_bit(HISTOIRE, s, true)
        | u8_set_bit(GEO, s, true)
        | u8_set_bit(PHILO, s, true);
    evaluer_eleve("litteraire", s);
    evaluer_eleve("scientifique", ~s);

    /* un élève bon en sport et en chimie... */
    s = 132;
    evaluer_eleve("mystère", s);

    s = 0;
    evaluer_eleve("toto", s);

    /* Deuxième chance pour toto, il passe les examens littéraires. */
    exam_t e = 0;
    e = u8_set_bit(FRANCAIS, e, true)
        | u8_set_bit(HISTOIRE, e, true)
        | u8_set_bit(GEO, e, true)
        | u8_set_bit(PHILO, e, true);

    printf("toto repasse ses exams...\n");
    s = passer_examen(e, s);
    evaluer_eleve("toto", s);

    return EXIT_SUCCESS;
}

```


</details>
