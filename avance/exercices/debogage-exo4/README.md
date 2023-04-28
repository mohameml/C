# Enoncé

L'objectif est de déboguer ce programme qui manipule des pointeurs et
tableaux un peu trop à la manière d'un apprenti sorcier.

Compilez-le et trouvez le bug à l'aide des méthodes adaptées de
débogage.

Jouez le jeu: votre compilateur devrait vous avertir, mais ignorez le
warning un moment et allez plus loin dans la compréhension du
problème.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/debogage-exo4/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Utilise le debugger (ddd pour une vision synthétique des tableaux)
  et arme toi de courage.
* Affiche les tableaux, les valeurs des cases, leurs
  adresses. Effectue ces affichages dans `main` d'abord puis dans
  `affiche_tab2`. Compare les résultats obtenus.
* L'etude de la memoire a l'aide de la commande gdb "x" est
  fondamentale pour comprendre l'adresse mémoire indiquée en erreur
  par valgrind.

</details>

# Compétences

* Passage en paramètre d'un tableau de pointeurs
* Passage en paramètre de pointeurs de pointeurs
* Utilisation de valgrind
* Utilisation de gdb/ddd
* Utilisation des options de compilation

# Difficulté

:star: :star: :star:
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
EXEC=debogage-exo4

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *~ *.o $(EXEC)

```

#### Corrigé du fichier debogage-exo4.c

```c
#include <stdio.h>

int tab[4][4] =
    { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };

int *tab2[] = { tab[0], tab[1], tab[2], tab[3] };


void affiche_tab(int tab[][4])
{
    int i, j;
    for (i = 0; i < 4; ++i) {
	for (j = 0; j < 4; ++j) {
	    printf("%2d ", tab[i][j]);
	}
	printf("\n");
    }
    printf("\n");
    fflush(stdout);
}

void affiche_tab2(int *tab[])
{
    int i, j;
    for (i = 0; i < 4; ++i) {
	for (j = 0; j < 4; ++j) {
	    printf("%2d ", tab[i][j]);
	}
	printf("\n");
    }
    printf("\n");
    fflush(stdout);
}

int main()
{
    affiche_tab(tab);
    affiche_tab2(tab2);
    affiche_tab2(tab);
    affiche_tab(tab2);
    return 0;
}


```


# Correction debogage-exo4

### Résumé : pointeurs de pointeurs et tableaux de pointeurs, ce n’est pas la même chose !

## Warnings compilation

    gcc -o debogage-exo4 debogage-exo4.c -std=c99 -Wall -Wextra -g
    debogage-exo4.c:51:15: warning: incompatible pointer types passing 'int [4][4]'
        to parameter of type 'int **' [-Wincompatible-pointer-types]
            affiche_tab2(tab);
                        ^~~
    debogage-exo4.c:34:24: note: passing argument to parameter 'tab' here
    void affiche_tab2(int *tab[])
                            ^
    debogage-exo4.c:52:14: warning: incompatible pointer types passing 'int *[4]' to
        parameter of type 'int (*)[4]' [-Wincompatible-pointer-types]
            affiche_tab(tab2);
                        ^~~~
    debogage-exo4.c:21:22: note: passing argument to parameter 'tab' here
    void affiche_tab(int tab[][4])
                        ^
    2 warnings generated.

## Valgrind

    gcc -o debogage-exo4 debogage-exo4.c -std=c99 -Wall -Wextra –g

    valgrind ./debogage-exo4
    ==22872== Memcheck, a memory error detector
    ==22872== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
    ==22872== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
    ==22872== Command: ./debogage-exo4
    ==22872==
    1  2  3  4
    5  6  7  8
    9 10 11 12
    13 14 15 16

    1  2  3  4
    5  6  7  8
    9 10 11 12
    13 14 15 16

    ==22872== Invalid read of size 4
    ==22872==    at 0x40064C: affiche_tab2 (debogage-exo4.c:39)
    ==22872==    by 0x4006F5: main (debogage-exo4.c:51)
    ==22872==  Address 0x200000001 is not stack'd, malloc'd or (recently) free'd
    ==22872==
    ==22872==
    ==22872== Process terminating with default action of signal 11 (SIGSEGV)
    ==22872==  Access not within mapped region at address 0x200000001
    ==22872==    at 0x40064C: affiche_tab2 (debogage-exo4.c:39)
    ==22872==    by 0x4006F5: main (debogage-exo4.c:51)
    ==22872==  If you believe this happened as a result of a stack
    ==22872==  overflow in your program's main thread (unlikely but
    ==22872==  possible), you can try to increase the size of the
    ==22872==  main thread stack using the --main-stacksize= flag.
    ==22872==  The main thread stack size used in this run was 10485760.
    ==22872==
    ==22872== HEAP SUMMARY:
    ==22872==     in use at exit: 0 bytes in 0 blocks
    ==22872==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
    ==22872==
    ==22872== All heap blocks were freed -- no leaks are possible
    ==22872==
    ==22872== For counts of detected and suppressed errors, rerun with: -v
    ==22872== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 4 from 4)
    Erreur de segmentation

## gdb/ddd

    gcc debogage-exo4.c -o debogage-exo4 -std=c99 -Wall -Wextra –g
    ddd ./ debogage-exo2
	   // Commenter les 2 premiers affiche_tab et affiche_tab2 pour se concentrer sur
          le affiche_tab2 suivant
	   // Usez et abusez de graph display ...

On explore d’abord `tab` dans `main()` : `tab` est un tableau de 4x4 entiers.

![](solution-ddd1.png)

On explore ensuite `tab2` dans `main()` : `tab2` est un tableau de 4 pointeurs sur des entiers.

![](solution-ddd2.png)

On explore `tab` dans `affiche_tab2(tab)`.

![](solution-ddd3.png)

On vérifie la taille d’un `int` et d’un `int *`.

![](solution-ddd4.png)

Dans `main()`, on affiche en binaire le contenu des adresses concernées (commande : `x/t` dans gdb et ddd).

![](solution-ddd5.png)

## Conclusion

`sizeof(int)` : 4 octets
`sizeof(int *)` : 8 octets
`affiche_tab2` attend en argument un tableau de pointeurs sur des entiers (`int *tab[]`), donc un tableau dont chaque cellule contient l’adresse d’une case mémoire contenant une valeur entière.
Lorsqu’on passe en argument `tab` qui est un tableau de 4 x 4 entiers, `tab` va être interprété dans `affiche_tab2` comme un tableau de pointeurs sur des entiers.
Ce sont les entiers 1 (`tab[0][0]`) et 2 (`tab[0][1]`) qui sont alors considérés ensemble comme l'adresse d'un `int *`, puisqu'il faut ici deux entiers pour occuper la place mémoire d'un `int *`.
Pour comprendre l’interprétation finale de cet ensemble de 2 valeurs, on utilise la commande `x/g` qui affiche l’interprétation de l’ensemble des 8 octets stockés à une adresse donnée. Dans l’exemple :

    (gdb) x/g &tab[0][0]
    0x600ae0 <tab>:	00000000000000000000000000000010 00000000000000000000000000000001
											 dec : 2						  dec : 1
Inversion de 1 et 2 dans l’interprétation des 8 octets probablement liée au stockage interne des octets (voir little / big endian).
Dans `affiche_tab2`, si on convertit cet ensemble binaire en hexadécimal, on obtient donc `0x200000001` (adresse qui est stockée dans `tab[0]` à l’intérieur d’`affiche_tab2`).
L’adresse ainsi interprétée `0x200000001` ne correspond à aucune case mémoire réservée par le programme.  Ce qui se traduit par des lectures illégales de mémoire dans valgrind.

On peut modifier légèrement l’exercice avec un `tab[4][2]` pour vérifier que tout est bien compris :

![](solution-ddd6.png)


</details>
