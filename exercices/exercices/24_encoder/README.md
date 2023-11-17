# Enoncé

Cet exercice va vous faire manipuler les fonctions de la libc
permettant la lecture/l'écriture caractère par caractère de
fichiers.

On cherche à générer une version codée d'un fichier contenant un
message en clair. L'utilisateur définit une clé comprise entre 1 et
25 qui permettra d'encoder le message. Voici le principe d'encodage
que l'on va implémenter ici dans la fonction `coder_lettre(var, clé)` :

* On note `k` la clé définie par l'utilisateur ;
* On commence par écrire la clé en première position dans le message
de sortie (pour décodage futur) ;
* Ensuite, pour chaque caractère `var` du message d'entrée:
écrire `coder_lettre(var, clé)` dans le message de sortie

L'algorithme de la fonction `coder_lettre(var, clé)` est décrit ci-dessous :

Si `var` est une lettre de l'alphabet (minuscule ou majuscule), on
remplace dans le message de sortie le caractère var par le caractère
positionné `k` positions plus loin dans la table ASCII. Par exemple,
si `var` vaut `'b'` et `k` vaut 3, on remplacera `var` dans le message de
sortie par le caractère `'e'`. En effet, si on considère `'b'` comme
étant l'origine du déplacement, on a `position('b') = 0`,
`position('c') = 1`, `position('d') = 2` et donc `position('e') = 3`.

On fera en sorte ici qu'une miniscule en entrée produise une
minuscule en sortie, de même pour les majuscules. Autrement
dit, vous devez faire en sorte que le suivant du caractère `'z'`
soit `'a'` et que le suivant du caractère `'Z'` soit `'A'`.

Ainsi l'encodage du caractère `'x'` avec la clé 4 donne le
caractère `'b'`. En effet, comme on considère que le suivant de `'z'` est
`'a'`, on a :

	coder_lettre('x', 1) qui renvoie 'y' ;
	coder_lettre('x', 2) qui renvoie 'z' ;
	coder_lettre('x', 3) qui renvoie 'a' ;
	coder_lettre('x', 4) qui renvoie 'b' ;

Si `var` n'est pas une lettre de l'alphabet, on copie le caractère tel
quel dans le message de sortie.

La clé doit être écrite sur un octet et non sous la forme d'une chaîne ASCII.
Sans cela, l'exécutable `decoder` ne fonctionnera pas.

Vous pourrez tester votre implémentation sur le fichier `fable.txt`
qui se trouve dans le répertoire de l'exercice, en lançant par exemple :

	./encoder fable.txt fable-codee.txt 7

Pour savoir si votre fichier est correctement encodé, passez-le en
paramètre du programme `decoder` qui se trouve aussi dans ce même
répertoire :

	./decoder fable-codee.txt

Si vous ne voyez pas s'afficher le contenu du message qui se trouve
dans `fable.txt` ici, c'est que vous n'avez pas fini de travailler!

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/encoder/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* jetez un oeil (mais gardez-en un pour la suite) aux manuels des
  fonctions: `atoi`, `fopen`, `fgetc`, `fputc`, `feof` et `isalpha` ;
* si votre fichier encodé termine par un caractère bizarre, vérifiez
  que vous n'essayez pas d'encoder le caractère spécial de fin de
  fichier (`eof`).
</details>

# Compétences

* Codage ASCII
* Ouverture de fichier
* Fermeture de fichier
* Lecture caractère par caractère
* Ecriture caractère par caractère
* Ecriture dans un fichier texte

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
TARGETS=encoder
TARGETS += enonce-decoder

all: $(TARGETS)

enonce-decoder:
	$(MAKE) -C ./decodeur

.PHONY: clean
clean:
	rm -f *~ *.o $(TARGETS)
	$(MAKE) -C ./decodeur clean

```

#### Corrigé du fichier encoder.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Vérifie que les arguments passés en ligne de commande sont conforme.
 *
 * Affiche un message d'usage si ce n'est pas le cas.
 *
 * @param argc la longueur du tableau argv
 * @param argv les arguments à analyser, sous la forme d'un tableau de chaines de caractères
 */
static void verif_params(int argc, char** argv)
{
    if (argc != 4 || atoi(argv[3]) < 1 || atoi(argv[3]) > 25) {
        fprintf(stderr, "Usage: %s input.txt output.txt key\n", argv[0]);
        fprintf(stderr, "où:\n");
        fprintf(stderr, "\t- input.txt est le nom du fichier texte a coder ;\n");
        fprintf(stderr, "\t- output.txt est le nom du fichier dans lequel enregistrer le texte codé ;\n");
        fprintf(stderr, "\t- key est un entier compris entre 1 et 25.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Encode une lettre en appliquant une rotation (codage de Cesar).
 *
 * @param c la lettre à encoder
 * @param cle la rotation à appliquer
 * @return char la lettre résultant de la rotation de c de cle positions
 */
static char coder_lettre(char c, uint8_t cle)
{
    /*
        islower est une fonction de ctype.h qui renvoie vrai si le
        caractère est alphabétique et minuscule.
    */
    char base = islower(c) ? 'a' : 'A';
    /*
        isalpha est une fonction de ctype.h qui renvoie vrai si le
        caractère est alphabétique.
    */
    if (isalpha(c)) {
        /*
            On fait un parcours circulaire sur l'intervalle a-z ou
            A-Z. cf man ascii.
        */
        c = (c - base + cle) % 26 + base;
    }
    /*
        #if 0 est une utilisation astucieuse du préprocesseur pour
       commenter du code.
    */
#if 0
    /* Solution alternative plus lisible mais moins performante. */
    if (isalpha(c)) {
        for (uint8_t i = 0; i < cle; i++) {
            switch (c) {
                /* Deux cas particuliers à traiter ici: le suivant de
                 * 'z' et celui de 'Z'. */
            case 'z':
                c = 'a';
                break;
            case 'Z':
                c = 'A';
                break;
            default:
                c++;
            }
        }
    }
#endif
    /* Pour que le compilateur soit content. */
    return c;
}


int main(int argc, char** argv)
{
    verif_params(argc, argv);

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    uint8_t cle = atoi(argv[3]);

    /*
        Ecrire la clé en première position dans le fichier de
        sortie...
    */
    fputc(cle, output);

    /*
        ... puis le contenu du fichier à coder auquel on a appliqué la
        méthode d'encodage.
    */
    while (!feof(input)) {
        char c = fgetc(input);
        if (feof(input)) {
            /*
                Si le caractère qu'on vient de lire avec fgetc est
                le caractère spécial de fin de fichier (eof), on
                s'arrête.
            */
            break;
        }
        c = coder_lettre(c, cle);
        fputc(c, output);
    }

    fclose(input);
    fclose(output);

    return EXIT_SUCCESS;
}

```


</details>
