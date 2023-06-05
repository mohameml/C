# Enoncé

Le programme ci dessous contient une erreur. Il compile et s'execute
sans soucis, si ce n'est cette satanée erreur de segmentation a la
fin...  Le but de cet exercice est de trouver la raison de cette
erreur en utilisant les outils de débogage adaptés, et notament de
comprendre l'analyse de la trace d'un programme. Pour cela utilisez la
commande `backtrace` (qui s'abrège en `bt`) de `gdb` afin de mieux
comprendre ce qui se passe et d'isoler et de corriger le probleme.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/debogage-trace/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Tableau + segfault... Dépassement?

</details>

# Compétences

* Utilisation de valgrind
* Utilisation de gdb/ddd
* Utilisation des options de compilation
* Affichage de traces

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
EXEC=trace

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


.PHONY: clean
clean:
	rm -f *~ *.o $(EXEC)


```

#### Corrigé du fichier trace.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void affiche_et_libere_tab(uint8_t** tab, uint8_t taille, uint8_t offset){
    /* Affiche la ligne courante */
    uint8_t i;
    for(i = 0; i < taille; i++) {
	printf("%3u ", tab[taille - offset][i]);
    }
    printf("\n");
    /* libere la memoire associee a la ligne qui vient d'etre lue */
    free(tab[taille - offset]);
    /* Affiche le reste du tableau par recursion */
    /*       Ici on boucle sur le tableau avec la variable offset allant de
     * 'taille' a 0, soit (taille+1) iterations, ce qui provoque un depassement
     * de memoire. La trace de notre progamme montre bien les 11 appels a la
     * fonction affiche_et_libere_tab alors que notre tableau n'a que 10 lignes.
     * De plus on sait que l'erreur a lieu lors de l'appel avec le parametre
     * offset a la valeur 0. Il faut donc corriger le code en remplacant le test
     * ci dessous par ceci : if (offset>1)
     */
    if (offset > 0) {
	affiche_et_libere_tab(tab, taille, offset - 1);
    }
}

int main(void)
{
    /* Construit un simple tableau a deux dimmensions contenant les tables de
     * multiplications
     */
    uint8_t taille = 10;
    uint8_t **tab = malloc(taille * sizeof(uint8_t *));
    uint8_t i, j;
    for(i = 0; i < taille; i++) {
	tab[i] = malloc(taille * sizeof(uint8_t));
	for(j = 0; j < taille; j++) {
	    tab[i][j] = (i + 1) * (j + 1);
	}
    }
    /* On affiche notre tableau */
    affiche_et_libere_tab(tab, taille, taille);
    /* On libere le dernier pointeur */
    free(tab);

    return EXIT_SUCCESS;
}

```


</details>
