# Énoncé

Cet exercice vous fera manipuler les opérateurs d'incrémentation et
d'affectation composés. Le but du jeu est de rétablir un affichage
correct (au niveau du sens de l'histoire). Rien de bien compliqué à
priori, alors pour corser un peu l'affaire, vous n'avez le droit
d'insérer dans le code ci-dessous que les mots suivants :

```c
++
--
+=
*=
/=
2
3
5
```

A noter que `+` tout seul ne fait pas partie de cette liste, et donc
que vous ne pouvez pas écrire `age + 5`. Bad luck!

Le point de départ pour cet exercice (squelette de code, énoncé) se trouve dans `exercices/base/capitaine/`.

# Ressources associées

Le PAPL [Les opérateurs du langage C](http://formationc.pages.ensimag.fr/prepa/prof/#papl/operateurs/) vous apprendra tout ce qu'il y a à savoir sur... euh... les opérateurs du langage C.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* trouver la différence entre :
```c
uint8_t x = 1;
printf("++x = %u", ++x);
printf("x = %u", x);
```
et :
```c
uint8_t x = 1;
printf("x++ = %u", x++);
printf("x = %u", x);
```

</details>

# Compétences

* Opérateur adresse de
* Opérateur d'indirection
* Fonction taille mémoire d'un type de donnée
* Allocation de mémoire dynamique type de donnée simple
* Libération de mémoire

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier alloc.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t** creer_matrice(uint32_t rang)
{
    uint32_t** mat = calloc(rang, sizeof(uint32_t*));
    for (uint32_t i = 0; i < rang; i++) {
        mat[i] = calloc(rang, sizeof(uint32_t));
    }

    return mat;
}

static uint32_t** creer_matrice_a_plat(uint32_t rang)
{
    size_t len = rang * sizeof(uint32_t*) + rang * rang * sizeof(uint32_t);
    void* area = calloc(len, sizeof(uint8_t));

    uint32_t** mat = (uint32_t**)area;
    for (uint32_t i = 0; i < rang; i++) {
        mat[i] = area + rang * sizeof(uint32_t*) + i * sizeof(uint32_t);
    }

    return mat;
}

static void initialiser_matrice(uint32_t** mat, uint32_t rang)
{
    for (uint32_t i = 0; i < rang; i++) {
        for (uint32_t j = 0; j < rang; j++) {
            printf("%u %u\n", i, j);
            mat[i][j] = i * rang + j;
        }
    }
}

static void afficher_matrice(uint32_t** mat, uint32_t rang)
{
    for (uint32_t i = 0; i < rang; i++) {
        for (uint32_t j = 0; j < rang; j++) {
            printf("%02u%s", mat[i][j], j == rang - 1 ? "\n" : " ");
        }
    }
    printf("\n");
}

static void liberer_matrice(uint32_t** mat, uint32_t rang)
{
    for (uint32_t i = 0; i < rang; i++) {
        free(mat[i]);
    }

    free(mat);
}

static void liberer_matrice_a_plat(uint32_t** mat)
{
    free(mat);
}

int main(void)
{
    const uint32_t rang = 8;

    uint32_t** mat = creer_matrice(rang);
    initialiser_matrice(mat, rang);
    afficher_matrice(mat, rang);
    liberer_matrice(mat, rang);

    uint32_t** matapla = creer_matrice_a_plat(rang);
    initialiser_matrice(matapla, rang);
    afficher_matrice(matapla, rang);
    liberer_matrice_a_plat(matapla);

    return EXIT_SUCCESS;
}

```


</details>
