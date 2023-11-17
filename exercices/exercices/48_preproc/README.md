# Enoncé

Ici, on illustre l'utilisation du préprocesseur. Comme son nom
l'indique, le préprocesseur passe avant tout le monde dans les
différentes passes de compilation. En particulier, il passe avant la
phase d'analyse syntaxique du programme C. Son rôle est de remplacer
toutes les directives préprocesseur (tout ce qui débute par #, comme
#include, #define, ...) par ce qu'elles représentent. Il travaille
directement sur le texte du programme. Par exemple, le préprocesseur
va remplacer toutes les étiquettes définies par des #define par ce
qu'elles représentent _dans le texte du programme_. Le compilateur
effectue ensuite l'analyse syntaxique de ce code modifié.

Par exemple, le code suivant :

```c
#define TOTO printf("pouet pouet!\n")

printf("Message caché: ");
TOTO;
```

sera remplacé par le préprocesseur par le code :

```c
printf("Message caché: ");
printf("pouet pouet!\n");
```

L'exercice consiste à observer et comprendre ce qui se passe quand
on compile le programme suivant. On vous encourage notamment à faire
l'effort d'effectuer la phase de préprocesseur sur papier, pour voir
si vous êtes capable de prédire ce que fait ce programme sans le
compiler/l'exécuter pour de vrai.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/preproc/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* demandez à votre compilateur de s'arrêter après l'action du
  préprocesseur avec l'option `-E`:

```
  gcc -E preproc.c
```
</details>

# Compétences

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

all: preproc

.PHONY: clean
clean:
	rm -f *~ *.o preproc

```

#### Corrigé du fichier preproc.c

```c
#include <stdlib.h>
#include <stdio.h>

#define BOWIE "ch?v=AZKcl4-tcuo\n"
#define oO printf(
#define DAVID "be.com/wat"
#define TO "utu"
#define TRIBUTE "https://www.yo"
#define Oo );

int main(void)
{
    /*
        On peut demander au compilateur de s'arrêter juste après l'action
        du préprocesseur avec l'option -E :

            gcc -E preproc.c

        On retrouve alors le texte du programme source après
        modification par le préprocesseur.  La fin de cette sortie est
        la plus intéressante, puisqu'on y retrouve la version modifiée
        du main (celle qui sera effectivement compilée et exécutée
        lorsqu'on exécute gcc preproc.c -o preproc) :

            int main(void)
            {
                printf( "https://www.yo" "utu" "be.com/wat" "ch?v=v--IqqusnNQ\n" );

                return 0;
            }
       */
    oO TRIBUTE TO DAVID BOWIE Oo

    return EXIT_SUCCESS;
}

```


</details>
