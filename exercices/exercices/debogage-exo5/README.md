# Enoncé

Des tableaux et des pointeurs.

L'objectif est de déboguer ce programme qui semble habité par des
fantômes mémoriels...

Compilez-le et trouvez les bugs à l'aide des méthodes adaptées de
débogage.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/debogage-exo5/`.

# Ressources associées

Allez lire la fiche de cours [Premier contact avec le débogage](http://formationc.pages.ensimag.fr/prepa/prof/papl/gdb/) et la fiche [Débogage mémoire](http://formationc.pages.ensimag.fr/prepa/prof/papl/valgrind/) avant de traiter cet exercice.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Utilisez `valgrind` pour une première indication ;
* Utilisez un debugger (`ddd` pour une visualisation plus simple des
  tableaux) ;
* Affichez les adresses et valeurs des éléments du tableau `i`, dans la
  fonction `f` et dans la fonction `g` ;
* Affichez les adresses et valeurs de `a` et `b`.

</details>

# Compétences

* Tableaux statiques
* Portée d'une variable dans un module, une fonction
* Opérateur d'indirection
* Utilisation de valgrind
* Utilisation de gdb/ddd

# Difficulté

:star: :star:
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
EXEC=debogage-exo5

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *~ *.o $(EXEC)

```

#### Corrigé du fichier debogage-exo5.c

```c
#include <stdio.h>

/*
  a et b sont 2 variables (pointeurs) globales.
  Elles ont une existence durant toute la vie de ce programme.
*/
int *a, *b;

void f(int x)
{
    /*
      i est un tableau local à la fonction f.
      i n'a d'existence et de mémoire réservée pour lui qu'à l'intérieur
      de cette fonction f. Dès la sortie de f, la mémoire attribuée à i
      est libérée automatiquement.
    */
    int i[3];
    i[0] = x;
    i[1] = x + 1;
    i[2] = x + 2;
    /*
      a pointe sur l'adresse de i.
      i étant libéré à la sortie de f, a pointera à la sortie de f
      sur une zone mémoire qui n'est plus attribuée au programme.
    */
    a = i;
}

void g(int x)
{
    /*
      i est un tableau local à la fonction g.
      i n'a d'existence et de mémoire réservée pour lui qu'à l'intérieur
      de cette fonction g. Dès la sortie de g, la mémoire attribuée à i est
      libérée automatiquement. Le problème ici est que le tableau i reprend
      "par hasard" la zone mémoire libérée par le tableau i de la fonction f.
      Cette zone mémoire sur laquelle pointe aussi a est modifiée par la
      fonction g, d'où l'affichage final.
    */
    int i[3];
    i[0] = x;
    i[1] = x + 1;
    i[2] = x + 2;
    b = i;
}

int main()
{
    f(1); /* Modifie a */
    printf("a = {%d,%d,%d}\n", a[0], a[1], a[2]);
    g(2); /* Modifie b */
    printf("Abracadabrantesque, a = {%d,%d,%d}\n", a[0], a[1], a[2]);
    return 0;
}


```

# Correction debogage-exo5 :
Résumé : attention à la portée des variables et à leur durée de vie.

## Compilation :
RAS, pas de warning.

## Valgrind :
Ici, plein d'erreurs!

    gcc -o debogage-exo5 debogage-exo5.c -std=c99 -Wall -Wextra –g

    valgrind ./debogage-exo5
    ==23513== Memcheck, a memory error detector
    ==23513== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
    ==23513== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
    ==23513== Command: ./debogage-exo5
    ==23513==
    ==23513== Use of uninitialised value of size 8
    ==23513==    at 0x3DAB243A9B: _itoa_word (_itoa.c:195)
    ==23513==    by 0x3DAB246652: vfprintf (vfprintf.c:1640)
    ==23513==    by 0x3DAB24F189: printf (printf.c:35)
    ==23513==    by 0x400577: main (debogage-exo5.c:62)
    ==23513==
    ==23513== Conditional jump or move depends on uninitialised value(s)
    ==23513==    at 0x3DAB243AA5: _itoa_word (_itoa.c:195)
    ==23513==    by 0x3DAB246652: vfprintf (vfprintf.c:1640)
    ==23513==    by 0x3DAB24F189: printf (printf.c:35)
    ==23513==    by 0x400577: main (debogage-exo5.c:62)
    ==23513==
    ==23513== Conditional jump or move depends on uninitialised value(s)
    ==23513==    at 0x3DAB2450E3: vfprintf (vfprintf.c:1640)
    ==23513==    by 0x3DAB24F189: printf (printf.c:35)
    ==23513==    by 0x400577: main (debogage-exo5.c:62)
    ==23513==
    ==23513== Conditional jump or move depends on uninitialised value(s)
    ==23513==    at 0x3DAB245101: vfprintf (vfprintf.c:1640)
    ==23513==    by 0x3DAB24F189: printf (printf.c:35)
    ==23513==    by 0x400577: main (debogage-exo5.c:62)
    ==23513==
    a = {1,2,3}
    ==23513== Use of uninitialised value of size 8
    ==23513==    at 0x3DAB243A9B: _itoa_word (_itoa.c:195)
    ==23513==    by 0x3DAB246652: vfprintf (vfprintf.c:1640)
    ==23513==    by 0x3DAB24F189: printf (printf.c:35)
    ==23513==    by 0x4005B6: main (debogage-exo5.c:64)
    ==23513==
    ==23513== Conditional jump or move depends on uninitialised value(s)
    ==23513==    at 0x3DAB243AA5: _itoa_word (_itoa.c:195)
    ==23513==    by 0x3DAB246652: vfprintf (vfprintf.c:1640)
    ==23513==    by 0x3DAB24F189: printf (printf.c:35)
    ==23513==    by 0x4005B6: main (debogage-exo5.c:64)
    ==23513==
    ==23513== Conditional jump or move depends on uninitialised value(s)
    ==23513==    at 0x3DAB2450E3: vfprintf (vfprintf.c:1640)
    ==23513==    by 0x3DAB24F189: printf (printf.c:35)
    ==23513==    by 0x4005B6: main (debogage-exo5.c:64)
    ==23513==
    ==23513== Conditional jump or move depends on uninitialised value(s)
    ==23513==    at 0x3DAB245101: vfprintf (vfprintf.c:1640)
    ==23513==    by 0x3DAB24F189: printf (printf.c:35)
    ==23513==    by 0x4005B6: main (debogage-exo5.c:64)
    ==23513==
    Abracadabrantesque, a = {2,3,4}
    ==23513==
    ==23513== HEAP SUMMARY:
    ==23513==     in use at exit: 0 bytes in 0 blocks
    ==23513==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
    ==23513==
    ==23513== All heap blocks were freed -- no leaks are possible
    ==23513==
    ==23513== For counts of detected and suppressed errors, rerun with: -v
    ==23513== Use --track-origins=yes to see where uninitialised values come from
    ==23513== ERROR SUMMARY: 24 errors from 8 contexts (suppressed: 4 from 4)

## gdb/ddd :

### Rappels (portée des variables et procédures)

`a` et `b` sont deux variables globales (deux pointeurs sur des entiers).

* dans la fonction `f` : `i` est un tableau local qui ne vit qu’à l’intérieur de la fonction `f` ;
* dans la fonction `g` : `i` est un (autre) tableau local qui ne vit qu’à l’intérieur de la fonction `g`.

`ddd` montre que :

* `a` prend l'adresse d'une variable locale `i` (dans `f`) qui disparait quand la fonction `f` retourne ;
* `b` prend l'adresse d'une variable locale `i` (dans `g`) qui reprend l'adresse libérée par `i` de `f` et qui disparait au retour de la fonction `g`.

![](solution-ddd1.png)
![](solution-ddd2.png)
![](solution-ddd3.png)
![](solution-ddd4.png)
![](solution-ddd5.png)
![](solution-ddd6.png)
![](solution-ddd7.png)

## Conclusion :

Ce qui est trompeur dans cet exemple, c’est que le tableau `i` dans la fonction `g` reprend la même adresse que celle du tableau `i` dans la fonction `f`. Hasard ou pas : oui et non. On est dans un programme très court où les appels des fonctions sont très rapprochés. Il n’est pas tout à fait illogique que le tableau `i` dans `g` reprenne dans certaines conditions la zone mémoire qui vient d’être laissée libre par le tableau `i` de la fonction `f`.
Ces tableaux `i` sont pourtant des variables locales dont les cases mémoires sont libérées à la sortie des fonctions.
Mais libérer une case mémoire ne veut pas dire supprimer le contenu binaire de cette case. En reprenant (plus ou moins par hasard) la même adresse pour le tableau `i` de `g` que le tableau `i` de `f`, on retombe sur le contenu en mémoire écrit dans `f` et qui n’a pas été effacé.


</details>
