# Énoncé

Big Brother a besoin d'un programme pour enregistrer des messages
textuels.

Il vous engage pour implémenter la fonction `log_message` qui écrit un
message dans un flux de sortie passé en paramètre.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/big-brother/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Utiliser la fonction `fputs` (`man fputs` dans un terminal pour
  savoir comment ça marche)

</details>

# Compétences

* Ecriture par ligne

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: big-brother

.PHONY: clean check

check:
	make -C tests/ check

clean:
	rm -f *~ *.o big-brother

```

#### Corrigé du fichier big-brother.c

```c
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Ecrit un message dans un flux passé en paramètre.
 *
 * @param stream le flux dans lequel écrire
 * @param message le message à écrire
 */
static void log_message(FILE* stream, const char* message)
{
    /* On écrit toute la ligne d'un coup! */
    int ret = fputs(message, stream);
    if (ret == EOF) {
        /* Si jamais ça se passe mal, on affiche un message d'erreur
         * explicite via la fonction perror, et on arrête le
         * programme. */
        perror("log_message: ");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    log_message(stdout, "Un message sur la sortie standard.\n");
    log_message(stderr, "Pis un autre sur la sortie d'erreurs, tiens!\n");

    FILE* f = fopen("log-secret.txt", "w");
    if (f == NULL) {
        perror("fopen log-secret.txt : ");
        exit(EXIT_FAILURE);
    }
    log_message(f, "Un dernier dans un fichier, pour la route. \
                    I am watching you.\n");
    fclose(f);

    return EXIT_SUCCESS;
}

```


</details>
