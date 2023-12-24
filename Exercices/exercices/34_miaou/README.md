# Enoncé

On manipule ici des fichiers en C. L'exercice consiste à programmer
un équivalent à la commande `cat` que vous connaissez déjà, plus
précisément au comportement de cette commande quand on lui fournit
une liste de fichiers en paramètre.

Votre programme C devra donc ouvrir les fichiers passés en
paramètre, puis afficher leur contenu sur la sortie standard, les
uns à la suite des autres. Si le programme est appelé sans
paramètre, un message d'erreur s'affiche et le programme termine.

Le code qui effectue l'ouverture du fichier, sa lecture, l'affichage
de son contenu et sa fermeture sera placé dans une fonction de
prototype :

```c
void cat_file(const char *file_name);
```

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/miaou/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* si le programme est appelé de cette façon:
```
./miaou toto.txt titi.txt
```
  alors:
```
argc vaut 3
argv[0] contient "./miaou"
argv[1] contient "toto.txt"
argv[2] contient "titi.txt"
```

* `fopen` permet d'ouvrir un fichier (`man fopen`) ;
* `fgetc` permet de lire un caractère dans un fichier (`man fgetc`) ;
* `fclose` permet de fermer un fichier (`man fclose`) ;
</details>

# Compétences

* Ouverture de fichier
* Fermeture de fichier
* Lecture caractère par caractère
* Affichage formaté sur la sortie standard
* Boucles while
* Découpage d'un module en fonctions
* Prototypes de fonctions
* Passage de paramètres au programme principal

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: miaou

.PHONY: clean
clean:
	rm -f *~ *.o miaou

```

#### Corrigé du fichier miaou.c

```c
#include <stdlib.h>
#include <stdio.h>

/*
    static limite la visibilité de cette fonction à ce fichier
    (miaou.c).
*/
static void cat_file(const char *file_name)
{
    /* On ouvre le fichier en lecture seulement. */
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        /*
            fopen renvoie NULL en cas d'erreur (cf man fopen). La
            variable errno est alors positionnée à une valeur
            explicite (un code), indiquant le type de l'erreur. La
            fonction perror affiche, en plus de la chaine de
            caractères passée en paramètre, une description de
            l'erreur correspondant au code stocké dans errno.
        */
        perror("cat_file: ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    /* On lit un caractère depuis le fichier f. */
    char c = fgetc(f);
    while (c != EOF) {
        /*
            EOF représente le caractère spécial indiquant la fin du
            fichier.
        */
        printf("%c", c);
        c = fgetc(f);
    }

    /*
        On ferme le fichier f. Si on ne fait pas ça, la mémoire
        associée au fichier f n'est pas libérée correctement, et
        valgrind râle.
    */
    fclose(f);
}

int main(int argc, char **argv)
{
    /*
        Affiche un message d'erreur si l'utilisateur oublie l'argument
        à passer en ligne de commandes.
    */
    if (argc < 2) {
        /*
            Le nom du programme compte dans le nombre d'arguments
            argc. Du coup, si on veut que le programme soit appelé
            avec au moins un argument, il faut vérifier que argc vaut
            au moins 2.
        */
        fprintf(stderr, "Usage: %s fichier1 ... fichierN\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
        Même remarque que précédemment, le premier argument est
        numéroté 1 (0 correspond au nom du programme).
    */
    for (int arg = 1; arg < argc; arg++) {
        cat_file(argv[arg]);
    }

    return EXIT_SUCCESS;
}

```


</details>
