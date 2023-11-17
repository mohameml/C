# Enoncé

Il arrive parfois que la libc vous parle, et que vous fassiez la sourde
oreille. En particulier, quand l'exécution d'une fonction de la bibliothèque
standard C se passe mal, il est très fréquent que cette fonction retourne
une valeur bien choisie, documentée dans le manuel, et positionne un code
d'erreur global (`errno`) qui représente le type d'erreur. On cherche ici à
obtenir cette information via l'utilisation de la fonction `perror()`.

On vous fournit un programme simple qui ouvre et ferme un fichier. Le `main()`
de ce programme peut exécuter deux scénarios différents, en fonction d'un
nombre passé en argument sur la ligne de commande (soit 1, soit 2).

Compilez ce programme. Si vous exécutez chacun des deux scénarios, vous vous
rendrez compte qu'ils terminent tous sur une erreur de segmentation. En
effet, l'exécution de la fonction `fopen()` de la libc se passe mal dans les
deux cas, mais comme on n'effectue aucune verification sur la valeur de
retour, on passe à côté de cette erreur, et le programme termine en jus de
boudin un peu plus loin.

Modifiez le corps des fonctions `ouvrir_fichier()` et `fermer_fichier()` de
manière à tester les valeurs de retour des fonctions de la libc utilisées,
et d'afficher un message explicite correspondant au type d'erreur rencontré
le cas échéant. On utilisera pour cela la fonction `perror()`, dont vous lirez
bien entendu le manuel.

Une fois cette modification effectuée, vérifiez que l'exécution des deux
scénarios affiche maintenant un message explicite avant de quitter le
programme.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/errno/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* `man fopen`;
* `man fclose` ;
* `man perror`.
</details>

# Compétences

* Gestion d'erreurs à base de perror

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: errno

.PHONY: clean

clean:
	rm -f *~ *.o errno

```

#### Corrigé du fichier errno.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Ouvre un fichier selon un mode passé en paramètre.
 *
 * @param filename le chemin d'accès au fichier à ouvrir
 * @param mode le mode dans lequel ouvrir le fichier (cf man fopen)
 * @return FILE* le fichier ouvert
 */
static FILE* ouvrir_fichier(const char* filename, const char* mode)
{
    FILE* fichier = fopen(filename, mode);
    /*
      Cf man fopen:

      RETURN VALUE
      Upon successful completion fopen(), fdopen() and freopen() return a FILE
      pointer. Otherwise, NULL is returned and errno is set to indicate the
      error.
    */
    if (fichier == NULL) {
        /* Erreur! On affiche un message explicite correspondant à la valeur
         * de errno à l'aide de perror(). */
        perror("[ouvrir_fichier] fopen");
        /* On arrête le programme, parce que l'utilisation de la variable
         * fichier par le reste du programme provoquerait une erreur à coup
         * sûr. */
        exit(EXIT_FAILURE);
    }
    return fichier;
}

/**
 * @brief Ferme le fichier passé en paramètre.
 *
 * @param fichier le fichier à fermer
 */
static void fermer_fichier(FILE* fichier)
{
    int ret = fclose(fichier);
    if (ret != 0) {
        perror("[fermer_fichier] fclose");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Affiche un message explicitant comment utiliser le programme
 *
 * @param progname le nom du programme
 */
static void usage(const char* progname)
{
    /* On commence par râler... */
    fprintf(stderr, "Usage: %s n\n", progname);
    fprintf(stderr, "\toù n l'entier 1 ou 2.\n");
    /* ... puis on s'en va en claquant la porte. (la fonction exit(code) permet
     * de quitter le programme avec le code de retour passé en paramètre.)*/
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    /* argv est un tableau de chaines de caractères, de taille argc, dont
     * chaque élément est un mot de la ligne de commande. Ainsi, argv[0]
     * représente le nom du programme, argv[1] le premier argument. */
    if (argc != 2) {
        /* On doit obligatoirement saisir un numéro de scénario sur la ligne
         * de commande. */
        usage(argv[0]);
    }

    /* On convertit l'argument en ligne de commande, qui est une chaine de
     * caractères en C, en entier. */
    uint8_t id = atoi(argv[1]);

    /* On aurait pu faire un switch() ici. */
    if (id == 1) {
        /* Premier scénario. */
        FILE* lecture_seule = ouvrir_fichier("lecture-seule.txt", "w");
        fermer_fichier(lecture_seule);
    } else if (id == 2) {
        /* Deuxième scénario. */
        FILE* inexistant = ouvrir_fichier("t-es-pas-la-mais-t-es-ou.txt", "r");
        fermer_fichier(inexistant);
    } else {
        /* Le numéro de scénario n'est pas bon, on râle. */
        usage(argv[0]);
    }

    return EXIT_SUCCESS;
}

```


</details>
