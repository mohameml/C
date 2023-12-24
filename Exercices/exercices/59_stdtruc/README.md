# Enoncé

Ici, il est question des flux de sortie, d'erreur, d'entrée et de la
lecture et écriture sur ces flux.

Ce que doit faire votre programme main :

Dans un premier temps :
- Utilisation des flux standards de sortie (écran), d'erreur (écran)
  et d'entrée (clavier)
- Afficher le message suivant sur la sortie standard :

```
Bienvenue chez les flux
Saississez des couples nom age (ex : doe 35)
sur une même ligne en validant par un retour chariot
Tapez Q pour quitter le programme
```

- Saisie sécurisée d'une ligne contenant un nom (à stocker dans la
  variable nom) et un age (à stocker dans la variable age)
- Si le caractère Q a été saisi en début de ligne : arrêter la lecture
  et terminer le programme
- S'il manque un élément attendu dans la ligne saisie (nom et/ou age)
  :
  * afficher le message suivant (exemple) sur la sortie d'erreur et passer à la lecture suivante :
```
Erreur de saisie, nom et/ou age manquant dans la chaine : doe
```
  * afficher sur la sortie standard le message :
```
####
```
- Si les 2 éléments attendus sont présents (nom et age) :
  * afficher sur la sortie standard le message suivant (exemple) :
```
nom = Connor - age = 19 ans
```

Directives de codage obligatoires : Saisies : utiliser impérativement
et uniquement la saisie sécurisée fgets + sscanf Affichages : utiliser
impérativement et uniquement les fonctons fprintf et fputs

Dans un deuxième temps (quand le premier temps est réalisé et ok) :
- Ne modifiez aucune ligne du code précédemment écrit
- Ajouter du code dans main pour effectuer les traitements suivants :
	  + Rediriger le flux d'entrée standard sur un fichier in.txt
	  + Rediriger le flux de sortie standard vers un fichier out.txt
	  + Rediriger le flux de sortie d'erreur vers un fichier err.txt
- Changer la valeur `#define REFLUX` et la mettre à true et exécuter
  le code rajouté ci-dessus quand `REFLUX` a pour valeur true

Vérifier le contenu des fichiers `out.txt` et `err.txt` après exécution de
ce nouveau code.

Le point de départ pour cet exercice (squelette de code,
énoncé) se trouve dans `exercices/avance/stdtruc/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Cf. documentation `fgets`, `sscanf`, `fprintf`, `stdout`, `stderr`, `stdin`,
  `fputs`
* Chercher la documentation sur la fonction `freopen` pour rediriger
  un stdxxx vers un fichier

</details>

# Compétences

* Lecture par ligne
* Ecriture par ligne
* Affichage formaté sur la sortie standard
* Affichage formaté sur la sortie d’erreur

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: stdtruc

.PHONY: clean
clean:
	rm -f *~ *.o stdtruc out.txt err.txt

```

#### Corrigé du fichier stdtruc.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define TAMPSIZE 100    // Taille maximale de la chaine tampon de
			// saisie sécurisée : 100 caractères
#define REFLUX false    // true si on veut rediriger les flux stdin,
			// stdout et stderr vers des fichiers, false
			// sinon
#undef REFLUX
#define REFLUX true     // true si on veut rediriger les flux stdin,
			// stdout et stderr vers des fichiers, false
			// sinon

int main(void)
{
    char nom[20];   // Variable de stockage du nom saisi
    uint16_t age;   // Variable de stockage de l'age saisi
    /* A compléter */
    char tampon[TAMPSIZE];

    if (REFLUX) {
	freopen("out.txt", "wt", stdout);
	freopen("in.txt", "rt", stdin);
	freopen("err.txt", "wt", stderr);
    }

    fputs("Bienvenue chez les flux\nSaississez des couples nom age (ex : doe 35)\nsur une même ligne en validant par un retour chariot\nTapez Q pour quitter le programme\n", stdout);

    while (fgets(tampon, TAMPSIZE, stdin) != NULL && tampon[0] != 'Q') {
	if (sscanf(tampon, "%s%hu", nom, &age) < 2) {
	    fprintf(stderr, "Erreur de saisie, nom et/ou age manquant dans la chaine : %s", tampon);
	    fputs("####\n", stdout);
	} else {
	    fprintf(stdout, "nom = %s - age = %hu ans\n", nom, age);
	    /* Equivalent à :
	    printf("nom = %s - age = %hu\n", nom, age);
	    */
	}
    }
    return EXIT_SUCCESS;
}

```


</details>
