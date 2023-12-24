# Enoncé

C'est un exercice de compréhension de code, vous n'avez rien à
ajouter à ce programme, il fonctionne déjà comme il faut! Par
contre, on vous demande de comprendre ce qu'il fait.

Vous pouvez bien sûr le compiler et le lancer pour voir ce qu'il
produit (c'était votre premier réflexe, pas vrai?). Par contre, son
temps d'exécution est un peu long, ce qui vous laisse du temps pour
lire et démystifier le code du fichier `mystere.c`.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/mystere/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* jetez un oeil au manuel de la commande "indent"
</details>

# Compétences

* Respect d'un coding style

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: mystere

.PHONY: clean
clean:
	rm -f *~ *.o mystere

```

#### Corrigé du fichier mystere.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
int64_t f(int64_t n){int64_t x,y;if(n < 2){return n;}x=f(n-1);y=f(n-2);return x+y;}int main(void){int64_t z=42+1;printf("%ld\n",f(z));return 0;}

/*
    Un petit coup de "indent -linux mystere.c" dans un terminal, et hop!

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
int64_t f(int64_t n)
{
	int64_t x, y;
	if (n < 2) {
		return n;
	}
	x = f(n - 1);
	y = f(n - 2);
	return x + y;
}

int main(void)
{
	int64_t z = 42 + 1;
	printf("%ld\n", f(z));
	return 0;
}

    C'est à peine plus lisible, pas vrai?
*/


```


</details>
