# Enoncé

L'objectif est de déboguer ce programme apparemment très simple.

1. Compilez-le à l'aide du `Makefile` fourni.
2. Exécutez-le en saisissant d'abord la valeur 0, puis 1 puis 2, puis
   5.
3. Observez les résultats et trouvez le(s) bug(s) à l'aide des
   méthodes adaptées de débogage.
4. Expliquez pourquoi 1 et 2 sont tout le temps affichés.
5. Expliquez pourquoi 0 ne s'affiche jamais.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/debogage-exo9/`.

# Ressources associées

Allez lire la fiche de cours [Premier contact avec le débogage](http://formationc.pages.ensimag.fr/prepa/prof/papl/gdb/) et la fiche [Débogage mémoire](http://formationc.pages.ensimag.fr/prepa/prof/papl/valgrind/) avant de traiter cet exercice.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Changez de compilateur dans le `Makefile` et utilisez `clang` au lieu de
  `gcc`;
* Utilisez un debugger, affichez la valeur de `value` et exécutez pas
à pas le programme.

</details>

# Compétences

* Opérateurs d'assignation
* Evaluation d'une instruction
* Condition simple if
* Utilisation des options de compilation

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
# Utiliser le Makefile suivant dans un premier temps pour tester l'exécutable
# Compléter ensuite avec les options que vous jugerez utiles
CC=gcc
CFLAGS=-std=c99
LDFLAGS=
EXEC=debogage-exo9

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *~ *.o $(EXEC)


```

#### Corrigé du fichier debogage-exo9.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    char saisie[3];
    uint16_t value;
    printf("Je lis dans vos pensees.\nPensez a un chiffre entre 0 et 2.\nTapez le au clavier, je ne regarde pas !\n");
    fgets(saisie, 3, stdin);
    value = atoi(saisie);
    /*
        value = 0 assigne la valeur 0 à la variable value.
        value = 0 renvoie aussi la valeur assignée : 0.
        Le test finalement effectué est donc équivalent à if (0).
        if évalue une expression à VRAI quand elle est différente de 0.
        Dans ce cas, le test if (0) est donc toujours FAUX.
        Les instructions de ce if ne sont donc jamais exécutées même si
        la valeur 0 est saisie au clavier.

        Dans un test, il faut utiliser l'opérateur de comparaison ==
        et non l'opérateur d'assignation =.
    */
    if (value = 0) {
        printf("Vous avez saisi la valeur 0\n");
    }
    /*
        value = 1 assigne la valeur 1 à la variable value.
        value = 1 renvoie aussi la valeur assignée : 1.
        Le test finalement effectué est donc équivalent à if (1).
        if évalue une expression à VRAI quand elle est différente de 0.
        Dans ce cas, le test if (1) est donc toujours VRAI.
        Les instructions de ce if sont toujours exécutées quelque soit
        la valeur saisie au clavier.
    */
    if (value = 1) {
        printf("Vous avez saisi la valeur 1\n");
    }
    /*
        value = 2 assigne la valeur 2 à la variable value.
        value = 2 renvoie aussi la valeur assignée : 2.
        Le test finalement effectué est donc équivalent à if (2).
        if évalue une expression à VRAI quand elle est différente de 0.
        Dans ce cas, le test if (2) est donc toujours VRAI.
        Les instructions de ce if sont toujours exécutées quelque soit
        la valeur saisie au clavier.
    */
    if (value = 2) {
        printf("Vous avez saisi la valeur 2\n");
    }
    printf("Exemple de valeur renvoyee par une assignation = %d\n", value = 3);
    return EXIT_SUCCESS;
}

```


</details>
