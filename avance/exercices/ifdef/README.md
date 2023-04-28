# Enoncé

L'objectif de cet exercice est d'utiliser le procédé de compilation
conditionnelle d'un programme C. En effet, le programme fourni se
comportera différemment selon si vous définissez la macro `V1` ou
`V2`. Votre objectif est de compiler à la main ce programme de telle
sorte qu'un message de félicitations apparaisse sur la sortie standard
lors de son exécution.

Dans un second temps, étendez ce programme pour que le message `"J'ai
tout compris, en fait!"` ne s'affiche que si la macro `BIEN_COMPRIS` a
été définie à une valeur supérieure à 42.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/ifdef/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* on définit une étiquette à la compilation à l'aide de l'option `-D`

</details>

# Compétences

* Option variable macro et compilation conditionnelle

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier ifdef.c

```c
#include <stdlib.h>
#include <stdio.h>

/* On définit une macro à la compilation à l'aide de l'option -D.
 * On pourra par exemple compiler ce programme de cette façon:
 *
 *     gcc -Wall -Wextra -std=c99 -DV1 ifdef.c -o ifdef
 */
int main(void)
{
    const char *blabla;

#ifdef V1
    blabla = "Félicitations, vous avez compilé la version 1 de ce programme!\n";
#elif defined(V2)
    blabla = "Félicitations, vous avez compilé la version 2 de ce programme!\n";
#else
    blabla = "Raté! Vous n'avez défini ni V1 ni V2 à la compilation.\n";
#endif

    printf("%s\n", blabla);
     /* Ici, on vérifie que la macro BIEN_COMPRIS a bien été définie à
      * une valeur supérieure à 42. Pour la définir, on utilise
      * l'option -DBIEN_COMPRIS=43 par exemple. */
#if BIEN_COMPRIS >= 42
    printf("J'ai tout compris, en fait!\n");
#endif
    return EXIT_SUCCESS;
}

```


</details>
