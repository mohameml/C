# Enoncé

Au menu de cet exercice: un mini profiler avec des constantes binaires
et hexadécimales, des opérateurs binaires.

Représentation simplifiée du profil d'un individu :
- 1 entier non signé sur 16 bits
- chaque position binaire correspond à une qualité ou un défaut
- `profil_noms` : tableau des noms de qualités/défauts
- `profil_masques` : tableau en parallèle des masques binaires
  correspondant à chaque qualité/défaut

Par exemple :
- la valeur binaire `1000000000000000` correspond à la qualité "Diplomate"
- la valeur binaire `0000000000010000` correspond au défaut "Blessant"

On appelera le programme de cette façon :

```
./profiler <valeur numérique du profil à tester en hexadécimal>
```

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/profiler/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Regardez la documentation sur les constantes `0x`, `0b`
* Cherchez aussi du côté des opérateurs binaires
* Jetez un oeil aussi sur les formats de saisie et d'affichage pour
  des valeurs hexadécimales

</details>

# Compétences

* Typage des constantes
* Opérateurs binaires

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: profiler

.PHONY: clean
clean:
	rm -f *~ *.o profiler

```

#### Corrigé du fichier profiler.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 16     // taille des tableaux profils_masques et profils_noms

/*  Definir ici 2 constantes hexadecimales : CON ayant pour valeur ff00 et PERLE ayant pour valeur 00ff
    CON représente ainsi un profil ayant tous les défauts et aucune qualité
    PERLE représente ainsi un profil ayant toutes les qualités et aucun défaut */
#define CON 0x00FF      // Que des défauts
#define PERLE 0xFF00    // Que des qualités

/*
    Affiche les qualités et défauts de l'individu ayant ce profil passé en paramètre
    Exemple d'affichage (la valeur du profil est à afficher en héxadécimal) :
    Voici les qualites et defauts de cet individu de profil (hexa) 1010 :
    Bienveillant Blessant
    Faire l'analyse simplifiée suivante du profil et afficher les messages correspondants :
    - Cas : tous les défauts et aucune qualité, afficher :
      Ouh la, attention, ce profil est celui d'un gros c... !
    - Cas : toutes les qualités et aucune défaut, afficher :
      Wouah, ce profil est celui d'une perle !
    - Cas : nombre de qualités supérieur ou égal au nombre de défauts, afficher :
      Ce profil est plutot bon.
    - Cas : nombre de qualités inférieur au nombre de défauts, afficher :
      Ce profil est plutot mauvais.
*/
/* Compléter les paramètres passés à la fontion : un profil, le tableau des masques de profil, le tableau des noms de profil */
void affiche_profil(
    uint16_t profil, const uint16_t *profil_masques, const char *profil_noms[SIZE]
)
{
    /* A compléter : code de la fonction */
    uint8_t nb_qualites = 0;
    uint8_t nb_defauts = 0;
    printf("Voici les qualites et defauts de cet individu de profil (hexa) %hx :\n", profil);
    for (uint8_t i= 0; i < SIZE; i++) {
	if ((profil & profil_masques[i]) == profil_masques[i]) {
	    printf("%s ", profil_noms[i]);
	    if (i <= 7) {
		nb_qualites++;
	    }
	    if (i > 7) {
		nb_defauts++;
	    }
	}
    }
    if (nb_qualites + nb_defauts > 0) {
	printf("\n");
    }
	switch(profil) {
	case CON:
		puts("Ouh la, attention, ce profil est celui d'un gros c... !");
		break;
	case PERLE:
		puts("Wouah, ce profil est celui d'une perle !");
		break;
	default :
	    if(nb_qualites >= nb_defauts) {
		puts("Ce profil est plutot bon.");
	    } else {
		puts("Ce profil est plutot mauvais.");
	    }
		break;
	}
}

/*
    main
*/
int main(int argc, char **argv)
{
    /* Tableau des masques de profil */
    /* A compléter : initialisation des valeurs de profil_masques avec des constantes binaires */
    const uint16_t profil_masques[SIZE] = {
	0b1000000000000000, 0b0100000000000000, 0b0010000000000000, 0b0001000000000000,
	0b0000100000000000, 0b0000010000000000, 0b0000001000000000, 0b0000000100000000,
	0b0000000010000000, 0b0000000001000000, 0b0000000000100000, 0b0000000000010000,
	0b0000000000001000, 0b0000000000000100, 0b0000000000000010, 0b0000000000000001
    };

    /* Tableau des noms des éléments de profil */
    const char *profil_noms[SIZE] = {
	"Diplomate", "Courageux", "Altruiste", "Bienveillant",
	"Empathique", "Honnete", "Loyal", "Gentil",
	"Intolerant", "Arrogant", "Abrupt", "Blessant",
	"Calculateur", "Cruel", "Hypocrite", "Indiscret"
    };

    /* Profil passé en paramètre */
    uint16_t profil;
    /* A compléter : remplir profil à partir des paramètres d'appel du programme
       et appeler affiche_profil */
    if(argc < 2) {
	printf("Paramètre attendu :\n");
	printf("- valeur de profil numérique en hexadécimal\n");
	printf("Exemple : ./profiler <valeur hexa : F1A0>\n");
	return EXIT_FAILURE;
    }
    sscanf(argv[1], "%hx", &profil);
    affiche_profil(profil, profil_masques, profil_noms);
    /* Fin A compléter */
    return EXIT_SUCCESS;
}

```


</details>
