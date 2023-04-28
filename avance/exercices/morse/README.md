# Enoncé

Cet exercice vous fera manipuler les notions de constantes, de
portée de variables ainsi que des fonctions avancées de traitement
de chaînes de caractères.

Attention : cet exercice comporte des notions de base et des notions
avancées.

La liste des caractères à prendre en compte est la suivante :
- l'ensemble des lettres minuscules de a à z compris ;
- l'ensemble des chiffres de 0 à 9 compris ;
- le caractère espace `' '`.

La liste des codes Morse correspondants aux caractères, les lettres
dans l'ordre puis les chiffres dans l'ordre et enfin le caractère
espace, est la suivante :

```
".-","-...","-.-.","-..",".","..-.","--.","....","..",
".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",
"...","-","..-","...-",".--","-..-","-.--","--..",".----",
"..---","...--","....-",".....","-....","--...","---..","---.",
"-----","//"
```

Directives de codage :

- Complétez le fichier entête `morse.h`;
- La liste des caractères sera stockée dans une constante globale
`texte_ref` de type tableau de caractères à une dimension, vous ferez
en sorte que cette constante globale ne soit visible que dans
`morse.c` ;
- La liste des codes Morse sera stockée dans une constante globale
`morse_ref` de type tableau de chaines de caractères à 2 dimensions,
vous ferez en sorte que cette constante globale ne soit visible que
dans `morse.c` ;
- Les fonctions avancées de traitement de chaînes de caractères
  pourront être utilisées (longueur, copie, comparaison, ...) ;
- Les constantes globales tableaux `texte_ref` et `morse_ref` seront
  initialisées lors de leur déclaration ;
- La fonction avancée `strtok` pourra aussi être utilisée dans
  `affiche_texte` pour découper la chaine en Morse en sous-chaines ;
- La fonction `affiche_morse` pourra prendre en compte des caractères
  majuscule ou minuscule ;
- Un fichier `test_morse.c` est fourni pour illustrer le
  fonctionnement désiré des fonctions de `morse.c`.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/morse/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Déclaration partielle de texte_ref :
```c
char texte_ref[NBCAR] // Avec NBCAR défini à 37
```
* Déclaration partielle de morse_ref :
```c
char morse_ref[NBCAR][NBMORSE]// Avec NBMORSE défini à 6
```
* Algorithme général : extraire les sous chaines correspondant à un
  code morse, comparer chaque sous chaine aux éléments du tableau
  `morse_ref` pour identifier l'indice du caractère correspondant dans
  le tableau `texte_ref`
* Utilisez les fonctions `strncmp`, `strcpy`, `strlen`, ...
* Pour découper une chaine en sous chaines, l'utilisation de `sscanf`,
  combinée à des opérations de pointeurs est possible, voire un
  traitement caractère par caractère. Mais la fonction `strtok` bien
  utilisée simplifie le travail
* Utilisation de `strtok` : copier le paramètre morse dans une chaine
  temporaire `temp_str` et travaillez sur ce `temp_str` (car `strtok`
  altère la chaîne traitée)
* fonction de conversion en minuscule : cf. fonction `tolower`

</details>

# Compétences

* Chaînes de caractères
* Notion de constante
* Fonctions de copies de chaines de caractères
* Fonctions de comparaisons de chaines de caractères
* Fonctions de longueur d'une chaine de caractères
* Boucles for
* Mise en oeuvre d'un fichier entête
* Macros de fichiers d'entête
* Prototypes de fonctions
* Portée d'une variable dans un module, une fonction
* Makefile simple

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=
EXEC=test_morse

# Makefile à compléter
all: $(EXEC)

$(EXEC): $(EXEC).o morse.o
	$(CC) -o $@ $^ $(LDFLAGS)

morse.o: morse.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
.PHONY: clean enonce
enonce:
	@echo "Complétez d'abord le Makefile pour compiler cet exercice."

clean:
	rm -f *~ *.o $(EXEC)

```

#### Corrigé du fichier morse.c

```c
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h> // bool
#include <ctype.h> // tolower
#include "morse.h"

#define NBCAR 37
#define NBMORSE 6

/* Constantes globales statiques */
static const char texte_ref[NBCAR] =
    {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r',
     's','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0',
     ' '};
static const char morse_ref[NBCAR][NBMORSE] =
    {{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},
    {".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},
    {"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."},{".----"},
    {"..---"},{"...--"},{"....-"},{"....."},{"-...."},{"--..."},{"---.."},{"---."},
    {"-----"},{"//"}};


/* help : fonction affichant tout le tableau du code morse pouvant
   être codé ou décodé par ce programme */
void help()
{
    for (uint16_t i=0; i<NBCAR; i++) {
        printf(" %c :  %s\n",texte_ref[i],morse_ref[i]);
    }
}

/* affiche_texte : fonction affichant le texte correspondant au code
   morse passe en paramètre */
void affiche_texte(char *morse)
{
    uint16_t i;
    bool trouve;
    /* Utilisation de la fonction strtok permettant d'extraire des
       sous chaines */
    char temp_str[strlen(morse)+1];
    strcpy(temp_str, morse);
    char *mot;
    mot = strtok(temp_str, " ");
    while (mot != NULL) {
        trouve = false;
        for (i=0; i<NBCAR; i++) {
            if (strncmp(mot, morse_ref[i], NBMORSE) == 0) {
                printf("%c",texte_ref[i]);
                trouve = true;
                break;
            }
        }
        if (!trouve) {
            printf("\n\nCe code morse (%s) n'existe pas !\n\n", mot);
        }
        mot = strtok(NULL, " ");
    }
    printf("\n");
}

/* affiche_morse : fonction affichant le code Morse correspondant au
   texte passé en paramètre */
void affiche_morse(char *texte)
{
    for (uint16_t i=0; i<strlen(texte); i++) {
        for (uint16_t j=0; j<NBCAR; j++) {
            if (tolower(texte[i])==texte_ref[j]) {
                printf("%s ", morse_ref[j]);
            }
        }
    }
    printf("\n");
}

```

#### Corrigé du fichier morse.h

```c
#ifndef _MORSE_H_
#define _MORSE_H_

/* Prototypes module morse*/
extern void affiche_morse(char *);
extern void affiche_texte(char *);
extern void help();

#endif

```

#### Corrigé du fichier test_morse.c

```c
#include<stdio.h>
#include<stdlib.h>
#include "morse.h"

/* main */
int main(void)
{
    help(); // Affiche la correspondance des caractères pris en charge et des codes Morse
    printf("Affichage du code Morse de la phrase : \"RMS Titanic SOS\"\n");
    affiche_morse("RMS Titanic SOS");
    printf("Affichage de la traduction du code Morse : \".-. -- ... // - .. - .- -. .. -.-. // ... --- ... // .---- ..... // .- ...- .-. .. .-.. // .---- ---. .---- ..---\"\n");
    affiche_texte(".-. -- ... //  - .. - .- -. .. -.-. // ... --- ... // .---- ..... // .- ...- .-. .. .-.. // .---- ---. .---- ..---");

    return EXIT_SUCCESS;
}

```


</details>
