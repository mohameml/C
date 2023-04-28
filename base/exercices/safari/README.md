# Énoncé

Cet exercice introduit la fonction `fprintf` que nous utiliserons ici pour
écrire des messages sur la sortie d'erreurs.

Quand on compile et qu'on lance ce programme, on est forcément déçu...

Par contre, si on se souvient de ses cours d'UNIX, on pourra rediriger
la sortie standard dans le fichier `toto.txt`, la sortie d'erreurs
dans `titi.txt`, pour ensuite participer au safari en tapant :

```
cat toto.txt titi.txt
```

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/safari/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* `commande > log.txt` redirige la sortie standard du programme `commande`
  vers le fichier `log.txt` ;
* `commande 2> errors.txt` fait pareil, mais pour la sortie d'erreurs.
</details>

# Compétences

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

all: safari

.PHONY: clean
clean:
	rm -f *~ *.o safari

```

#### Corrigé du fichier safari.c

```c
#include <stdlib.h>
#include <stdio.h>

/*
    ./safari > toto.txt
    pour rediriger la sortie standard (ici, les printf()) dans le fichier toto.txt

    ./safari 2> titi.txt
    pour rediriger la sortie d'erreurs (ici, les fprintf(stderr, ...)) dans le fichier titi.txt

    cat toto.txt titi.txt
    pour afficher la ménagerie!
*/

int main(void)
{
    printf("              ___.-~\"~-._   __....__\n");
    printf("            .'    `    \\ ~\"~        ``-.\n");
    fprintf(stderr, "                      ,-.             __\n");
    printf("           /` _      )  `\\              `\\\n");
    fprintf(stderr, "                    ,'   `---.___.---'  `.\n");
    fprintf(stderr, "                  ,'   ,-                 `-._\n");
    printf("          /`  a)    /     |               `\\\n");
    fprintf(stderr, "                ,'    /                       \\\n");
    printf("         :`        /      |                 \\\n");
    printf("    <`-._|`  .-.  (      /   .            `;\\\\\n");
    fprintf(stderr, "             ,\\/     /                        \\\\\n");
    fprintf(stderr, "         )`._)>)     |                         \\\\\n");
    fprintf(stderr, "         `>,'    _   \\                  /       ||\n");
    printf("     `-. `--'_.'-.;\\___/'   .      .       | \\\\\n");
    printf("  _     /:--`     |        /     /        .'  \\\\\n");
    fprintf(stderr, "           )      \\   |   |            |        |\\\\\n");
    fprintf(stderr, "  .   ,   /        \\  |    `.          |        | ))\n");
    printf(" (\"\\   /`/        |       '     '         /    :`;\n");
    fprintf(stderr, "  \\`. \\`-'          )-|      `.        |        /((\n");
    fprintf(stderr, "   \\ `-`   .`     _/  \\ _     )`-.___.--\\      /  `'\n");
    printf(" `\\'\\_/`/         .\\     /`~`=-.:        /     ``\n");
    printf("   `._.'          /`\\    |      `\\      /(\n");
    fprintf(stderr, "    `._         ,'     `j`.__/           `.    \\\n");
    fprintf(stderr, "      / ,    ,'         \\   /`             \\   /\n");
    printf("                 /  /\\   |        `Y   /  \\\n");
    printf("                J  /  Y  |         |  /`\\  \\\n");
    fprintf(stderr, "      \\__   /           _) (               _) (\n");
    fprintf(stderr, "        `--'           /____\\             /____\\ \n");
    printf("               /  |   |  |         |  |  |  |\n");
    printf("              \"---\"  /___|        /___|  /__|\n");
    printf("                     '\"\"\"         '\"\"\"  '\"\"\"\n");

    return EXIT_SUCCESS;
}

```


</details>
