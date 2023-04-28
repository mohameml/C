# Enoncé

L'objectif est de déboguer ce programme comportant un bug "évident".
Compilez-le et trouvez le bug à l'aide des méthodes adaptées de
débogage.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/debogage-exo1/`.

# Ressources associées

Allez lire la fiche de cours [Premier contact avec le débogage](http://formationc.pages.ensimag.fr/prepa/prof/papl/gdb/) et la fiche [Débogage mémoire](http://formationc.pages.ensimag.fr/prepa/prof/papl/valgrind/) avant de traiter cet exercice.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Compiler à l'aide des options `-g -Wall -Wextra -std=c99` ;
* Lancez valgrind sur l'exécutable généré ;
* A l'aide de `gdb` ou `ddd`, tracer les valeurs de `*age`, `age`.

</details>

# Compétences

* Options warnings
* Option de debug
* Opérateur adresse de
* Utilisation de valgrind
* Utilisation de gdb/ddd
* Utilisation des options de compilation

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
# Compléter le Makefile effectuant les opérations suivantes :
# - Génération de l'exécutable : <nomexecutable>
# - <nomexecutable> : avec options de compilation standards et mode débogage pour utilisation de ddd/gdb et valgrind
# - Règle clean : supprimer les fichiers .o et l'exécutable généré 
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=
EXEC=debogage-exo1

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *~ *.o $(EXEC)

```

#### Corrigé du fichier debogage-exo1.c

```c
#include <stdio.h>

int main()
{
	/*
        age est un pointeur sur entier mais il n'est pas défini par un malloc par exemple.
		Il n'y a, à ce stade, aucune case mémoire réservée pour stocker un entier.
		gdb / ddd : age vaut 0x0 soit le pointeur NULL
		Message valgrind : uninitialzed value
	*/
	int *age;

	printf("Bonjour,\n");
	printf("Entrez votre age\n");
	/*
        La syntaxe est correcte car age est bien un pointeur.
		Mais comme age ne pointe sur aucune zone mémoire réservée/allouée.
		Il est impossible d'écrire une valeur dans cette zone mémoire non définie.
		Message valgrind : illegal write...
	*/
	scanf("%d", age);
	/*
        La syntaxe est correcte car *age désigne bien une valeur entière.
		Mais *age représente le contenu d'une zone mémoire non réservée/allouée.
		Il est impossible de lire une valeur dans cette zone mémoire non définie.
	*/
	printf("Vous avez %d ans\n", *age);
	return 0;
}

```

# Correction debogage-exo1

Résumé : variable age non allouée (pointeur sans allocation, non utilisable en l'état)

### Warnings à la compilation

    gcc debogage-exo1.c -o debogage-exo1 -std=c99 -Wall -Wextra -g
    debogage-exo1.c:33:14: warning: variable 'age' is uninitialized when used here
        [-Wuninitialized]
            scanf("%d", age);
                        ^~~
    debogage-exo1.c:22:10: note: initialize the variable 'age' to silence this
        warning
            int *age;
                    ^
                    = NULL
    1 warning generated.

### Valgrind : Use of unitialized value of size 8

    gcc debogage-exo1.c -o debogage-exo1 -std=c99 -Wall -Wextra –g
    valgrind ./debogage-exo1
    ==21002== Memcheck, a memory error detector
    ==21002== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
    ==21002== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
    ==21002== Command: ./debogage-exo1
    ==21002==
    10
    Bonjour,
    Entrez votre age
    ==21002== Use of uninitialised value of size 8
    ==21002==    at 0x3DAB256C50: _IO_vfscanf (vfscanf.c:1772)
    ==21002==    by 0x3DAB26444C: __isoc99_scanf (isoc99_scanf.c:37)
    ==21002==    by 0x400565: main (debogage-exo1.c:33)
    ==21002==
    ==21002== Use of uninitialised value of size 8
    ==21002==    at 0x400572: main (debogage-exo1.c:40)
    ==21002==
    Vous avez 10 ans
    ==21002==
    ==21002== HEAP SUMMARY:
    ==21002==     in use at exit: 0 bytes in 0 blocks
    ==21002==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
    ==21002==
    ==21002== All heap blocks were freed -- no leaks are possible
    ==21002==
    ==21002== For counts of detected and suppressed errors, rerun with: -v
    ==21002== Use --track-origins=yes to see where uninitialised values come from
    ==21002== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 4 from 4)

### gdb/ddd : adresse age = 0x0

    gcc debogage-exo1.c -o debogage-exo1 -std=c99 -Wall -Wextra –g
    ddd ./ debogage-exo1
	   graph display age

![screenshot ddd](solution-ddd.png)

### Conclusion :

`age` est un pointeur sur un entier. Il est sensé contenir l’adresse d’une case mémoire qui contiendra elle-même un entier. Le problème est que cette case mémoire n’est pas réservée (par un malloc par exemple) : `ddd` affiche une adresse indéfinie `0x0`, `valgrind` signale que `scanf` a un paramètre non initialisé (le pointeur `age`). Selon le compilateur utilisé, un message de type _illegal write_ (tentative d’écriture dans une case mémoire non réservée) peut aussi apparaitre ainsi qu’un message à l’exécution du programme : _Segmentation fault_.


</details>
