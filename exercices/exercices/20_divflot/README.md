# Enoncé

Le programme sur lequel on travaille ici effectue la division de deux
nombres entiers passés en argument sur la ligne de commande et affiche
le résultat.

On souhaite s'appuyer sur les directives de préprocesseur pour générer
deux versions de ce programme à partir d'un même fichier source : une
version travaillant avec des nombres réels simple précision (`float`),
l'autre travaillant sur des nombres réels double précision (`double`).

Le Makefile fourni génère déjà ces deux versions à partir du fichier
`divflot.c`.  Vous remarquerez que la seule différence entre les
règles de compilation générant `divflot-simple.o` et
`divflot-double.o` est la présence ou non du flag de compilation
`-DDOUBLE_PREC`. Ce flag définit (`-D`) l'étiquette `DOUBLE_PREC` pour
le préprocesseur, ce qui a pour effet d'activer la compilation des
portions de code se trouvant à l'intérieur d'un bloc `#ifdef
DOUBLE_PREC`.

A titre d'exemple, nous avons défini une étiquette `MESSAGE` qui sera
remplacée par le préprocesseur (donc avant la phase de compilation du
programme) par :
- la chaine de caractères `"Mode double"` si l'étiquette `DOUBLE_PREC`
  a été définie ;
- la chaine de caractères `"Mode float"` sinon.

Votre travail va donc consister à utiliser le préprocesseur pour
remplacer toutes les occurrences de `float` par `double` dans le cas
où l'étiquette `DOUBLE_PREC` est définie.

Voici un exemple de comportement attendu de votre programme :

```
./divflot-simple 5 3
Mode float
5 / 3 = 1.666666626930236816

./divflot-double 5 3
Mode double
5 / 3 = 1.666666666666666741
```

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/divflot/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

- vous pouvez appeler explicitement le préprocesseur à l'aide de
  l'option `-E` de gcc.
- par exemple, `gcc -E -DDOUBLE_PREC divflot.c` affichera sur la
  sortie standard le fichier `divlot.c` après passage du préprocesseur
  (c'est-à-dire après remplacement de toutes les instructions
  #quelquechose). C'est ce fichier qui sera ensuite compilé par le
  compilateur gcc. Consulter la sortie de `gcc -E` permet de
  comprendre les modifications apportées par le préprocesseur.

</details>

# Compétences

* Option variable macro et compilation conditionnelle
* Préprocesseur (define)

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: divflot-simple divflot-double

divflot-simple: divflot-simple.o

divflot-simple.o: divflot.c
	$(CC) $(CFLAGS) -c divflot.c -o divflot-simple.o

divflot-double: divflot-double.o

divflot-double.o: divflot.c
	$(CC) $(CFLAGS) -DDOUBLE_PREC -c divflot.c -o divflot-double.o

.PHONY: clean
clean:
	rm -f *~ *.o divflot-simple divflot-double

```

#### Corrigé du fichier divflot.c

```c
#include <stdlib.h>
#include <stdio.h>

#ifdef DOUBLE_PREC
#define MESSAGE "Mode double\n"
/*
    On demande ici au préprocesseur de remplacer dans le texte du programme (le code)
    toutes les occurrences du mot "float" par "double".

    Notez que c'est un peu bourrin par rapport à ce qu'on souhaite faire ici,
    parce qu'on ne fait pas la différence entre les réels qu'on utilise pour le calcul
    et d'autres variables de type float qu'on pourrait utiliser par ailleurs.

    On pourrait de manière plus portable définir les variables dont on souhaite
    définir la précision à la compilation comme étant de type "reel", puis utiliser
    le préprocesseur pour remplacer toutes les occurrences du mot "reel" dans le code
    par soit "float" soit "double", en fonction de la définition ou non de l'étiquette
    DOUBLE_PREC.
*/
#define float double
#else
#define MESSAGE "Mode float\n"
#endif /* DOUBLE_PREC */

int main(int argc, char **argv)
{
    /* Affiche un message d'erreur si l'utilisateur oublie l'argument
     * à passer en ligne de commandes. */
    if (argc < 3) {
	fprintf(stderr, "Usage: %s x y\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    printf(MESSAGE);

    /* Convertit le premier argument passé par l'utilisateur en entier. */
    int x = atoi(argv[1]);

    /* Convertit le deuxième argument passé par l'utilisateur en entier. */
    int y = atoi(argv[2]);

    /* On effectue la division! */
    float res = (float)x / (float)y;

    /*
	On affiche le résultat avec jusqu'à 20 chiffres
	avant la virgule et jusqu'à 18 chiffres après la virgule.
    */
    printf("%d / %d = %20.18f\n", x, y, res);

    return EXIT_SUCCESS;
}

```


</details>
