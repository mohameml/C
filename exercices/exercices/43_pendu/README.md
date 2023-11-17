# Enoncé

On souhaite implémenter une interface en ligne de commande pour une
variante du jeu du pendu. L'utilisateur va devoir trouver un mot
représenté par une chaine de caractères constante dans le programme. A
chaque tour de jeu, le joueur propose une lettre sur la ligne de
commande. Si cette lettre fait partie du mot à trouver, le programme
dévoile toutes les occurrences de cette lettre dans le mot. Les
lettres qui n'ont pas encore été trouvées sont affichées à l'aide du
caractère `'_'`.

Voici un exemple de sortie du programme :

```
______ : choisissez une lettre :
n
___n__ : choisissez une lettre :
t
___nt_ : choisissez une lettre :
b
b__nt_ : choisissez une lettre :
a
Raté! 'a' ne figure pas dans le mot à trouver...
b__nt_ : choisissez une lettre :
o
bo_nt_ : choisissez une lettre :
u
bount_ : choisissez une lettre :
y
Mot trouvé en 7 coups!
```

Vous remarquerez que le programme doit compter le nombre de
propositions effectuées pour arriver au résultat. Il doit aussi
afficher un message explicite lorsque la lettre proposée ne fait pas
partie du mot à trouver.

On utilisera un tableau de caractères (un tampon) qui contiendra les
lettres découvertes en cours de partie. Dans l'exemple ci-dessus, ce
tampon contient successivement `"______"` puis `"___n__"` puis
`"___nt_"`, ...

On utilisera la fonction `getchar()` pour récupérer un caractère entré
au clavier.  Tout caractère proposé par l'utilisateur qui n'est pas
alphabétique doit être ignoré (`man isalpha`). On impose l'utilisation
d'une structure de contrôle `do while()` pour traiter cette partie.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/pendu/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* `snprintf`, `isalpha`, `getchar`, `strcmp` peuvent vous aider ;
* pour la construction do while(), il y a aussi un exo "do-while" dans
le parcours de base, jetez-y un oeil si ça coince!

</details>

# Compétences

* Caractères
* Chaînes de caractères
* Traitement caractère par caractère
* Boucles do while

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: pendu

.PHONY: clean
clean:
	rm -f *~ *.o pendu

```

#### Corrigé du fichier pendu.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(void)
{
    /* La chaine de caractères à trouver, à changer selon votre inspiration. */
    const char *a_trouver = "bounty";
    /*
        Le tampon représentant les lettres trouvées / à trouver.
        Sa taille est bien strlen(a_trouver) + 1, puisque la fonction
        strlen() retourne le nombre de caractères précédant le caractère
        de fin de chaine (\0) qu'il faut donc compter à part.
    */
    size_t taille_chaine = strlen(a_trouver) + 1;
    char tampon[taille_chaine];

    /* Compteur de propositions, si on fait plus de 2^32 - 1 propositions, on est mal! */
    uint32_t n_fois = 0;

    /*
        On initialise le tampon à l'aide de snprintf(),
        qui permet d'écrire dans une chaine de caractères
        une autre chaine obtenue à l'aide d'une chaine de format
        (%quelquechose, comme ce qu'on passe en paramètre de
        printf pour afficher la valeur d'une variable).

        Ici, %s est remplacé par la chaine de caractères constante
        "______" pour former une chaine qui sera écrite dans tampon.

        snprintf(tampon, taille_chaine, "%s%s%d%s", "trop ", "bi", 1, " snprintf!");
        aurait fait tout autre chose! Si vous ne savez pas quoi, ben... Essayez!
    */
    snprintf(tampon, taille_chaine, "%s", "______");

    /*
        On utilise strcmp pour tester l'égalité de deux chaines de caractères,
        ici la chaine à trouver et le tampon. Vous remarquerez que strcmp() ne
        renvoie pas un booléen mais le nombre de différences entre les deux chaines.
        Du coup, si c'est 0, les chaines sont identiques!
     */
    while (strcmp(tampon, a_trouver) != 0) {
        printf("%s : choisissez une lettre :\n", tampon);
        char c;
        do {
            /* Ici, on récupère un caractère entré au clavier ... */
            c = getchar();
            /* ... et on boucle tant que ce caractère n'est pas une lettre. */
        } while (!isalpha(c));

        /*
            Cette variable permettra d'indiquer si la lettre proposée
            était bien dans le mot à trouver.
        */
        bool appartient = false;
        /* On parcourt les caractères de la chaine à trouver. */
        for (size_t i = 0; i < strlen(a_trouver); i++) {
            /*
                Si le caractère en position i est identique au caractère proposé,
                on dévoile le caractère en position i dans le tampon.
            */
            if (c == a_trouver[i]) {
                tampon[i] = c;
                appartient = true;
            }
        }

        /* On n'a trouvé aucune occurrence du caractère dans le mot à trouver... */
        if (!appartient) {
            printf("Raté! '%c' ne figure pas dans le mot à trouver...\n", c);
        }

        /* On n'oublie pas d'incrémenter le compteurs de propositions! */
        n_fois++;
    }

    printf("Mot trouvé en %u coups!\n", n_fois);

    return EXIT_SUCCESS;
}

```


</details>
