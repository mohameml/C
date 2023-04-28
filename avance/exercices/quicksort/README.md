# Enoncé

Les étudiants de 1ère année Ensimag doivent élire leur représentant.
Le vote effectué, le dépouillement à lieu et il vous incombe de
publier les résultats.  Qui de François, Alain ou Nicolas sera choisi?

Les résultats de l'élection devront être affichés de deux façons :
- sous la forme d'un listing trié par ordre alphabétique ;
- sous la forme d'un listing trié par pourcentage de voix.

Les candidats sont représentés sous la forme d'un tableau de
structures qu'il faudra trier en fonction du critère choisi.

L'utilisation de la fonction `quicksort()` est OBLIGATOIRE dans cet
exercice, puisqu'il a pour but de vous faire travailler les pointeurs
de fonction et le passage de paramètres de la forme (`void *`).

Dans la vraie vie, on n'utilisera jamais `quicksort()` pour trier un
tableau de 7 éléments (demander pourquoi à votre prof d'algo préféré).

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/quicksort/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* man qsort

* un pointeur de fonction est toujours défini de la même façon :
```c
type_retour (*nom_fonction)(type_arg1, type_arg2, ..., type_argN)
```

définit une variable de type pointeur de fonction dont le nom est
`nom_fonction`.  La fonction pointée retourne une valeur de type
`type_retour`, son premier paramètre doit être de type `type_arg1`,
etc.

* si vous ne pigez pas comment `qsort` fonctionne, essayez d'écrire un
 petit programme de test qui trie un tableau de 10 entiers. Et si vous
 bloquez là-dessus, appelez un ami! (ou un enseignant)

</details>

# Compétences

* Transtypage de types avancés
* Pointeurs sur void
* Pointeurs de fonctions

# Difficulté

:star: :star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: quicksort

.PHONY: clean
clean:
	rm -f *~ *.o quicksort

```

#### Corrigé du fichier quicksort.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NB_ETUS 7

/* Structure de données représentant un étudiant. */
struct etu {
    /* Nom de l'étudiant. */
    char *nom;
    /* Son score, sur 100. */
    float score;
};

/* Affiche le tableau d'étudiants passé en paramètre. */
static void afficher_etudiants(struct etu diants[NB_ETUS]) {
    for (size_t i = 0; i < NB_ETUS; i++) {
        printf("%s: %2.1f\n", diants[i].nom, diants[i].score);
    }
}

/*
    Le prototype de qsort est :
    void qsort(void *base, size_t nel, size_t width,
         int (*compar)(const void *, const void *));
    (cf man qsort)

    Le dernier paramètre est la fonction de comparaison
    qui sera utilisée pour trier le tableau d'adresse
    base.

    Le format du pointeur de fonction indique que le paramètre
    compar doit être une fonction qui retourne un int et qui
    prend deux variables de type const void * en paramètre.

    Ces variables contiendront les adresses des deux élements du
    tableau à comparer. Les fonctions compare_notes et compare_noms
    ci-dessous ont été définies pour être compatibles avec qsort.
    C'est pourquoi leur prototype correspond à celui imposé par le pointeur
    de fonction int (*compar)(const void *, const void *).
*/

static int compare_notes(const void *e1, const void *e2) {
    /* On récupère les adresses des deux étudiants à comparer. */
    struct etu *etu1 = (struct etu *)e1;
    struct etu *etu2 = (struct etu *)e2;

    /* Une fonction de comparaison doit renvoyer un entier strictement négatif
       si e1 < e2, nul si e1 == e2 et strictement positif si e1 > e2
       (voir man qsort encore une fois).
     */
    return etu1->score - etu2->score;
}

static int compare_noms(const void *e1, const void *e2) {
    struct etu *etu1 = (struct etu *)e1;
    struct etu *etu2 = (struct etu *)e2;

    /* Ici, on utilise directement strcmp pour comparer les deux chaines
       de caractères, qui renvoie exactement ce qu'on veut (bizarrement!)
     */
    return strcmp(etu1->nom, etu2->nom);
}

int main(void)
{
    struct etu diants[NB_ETUS] = {
        { "François", 44.1 },
        { "Jean-Frédéric", 1.5 },
        { "Alain", 28.6 },
        { "Bruno", 2.4},
        { "Nicolas", 20.7 },
        { "Nathalie", 2.6 },
        { "Jean-François", 0.3 }
    };

    /* TODO : On trie les étudiants en fonction de leurs notes en utilisant qsort() */
    qsort(diants, NB_ETUS, sizeof(struct etu), compare_notes);
    printf("Classés par notes croissantes :\n");
    afficher_etudiants(diants);

    /* TODO : On trie les étudiants par ordre alphabétique en utilisant qsort() */
    qsort(diants, NB_ETUS, sizeof(struct etu), compare_noms);
    printf("\nClassés par ordre alphabétique :\n");
    afficher_etudiants(diants);

    return EXIT_SUCCESS;
}

```


</details>
