# Enoncé

Cet exercice illustre une des différences entre l'écriture avec
`fprintf` sur la sortie standard ou la sortie d'erreurs.
Exo facile en termes de programmation, il n'y a rien à faire !
Par contre il faut constater/comprendre ce qui se passe; qu'en retirer?

Le point de départ pour cet exercice (squelette de code,
énoncé) se trouve dans `exercices/base/pingpong/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Avec la sortie standard, écrivez-vous bien directement dans la console?
* Essayez de commenter un des fprintf à la fois. Observez les changements.
* Rajoutez un '\n' dans le fprintf où il n'y en a pas. Observez les changements
* Cherchez ce que fait la fonction fflush. Essayez de l'utiliser. Observez les changements.
</details>

# Compétences

* Affichage formaté sur la sortie standard
* Affichage formaté sur la sortie d’erreur

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: pingpong

.PHONY: clean
clean:
	rm -f *~ *.o pingpong

```

#### Corrigé du fichier pingpong.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*
   Comme vous le voyez, la trace n'est pas exactement celle attendue,
   avec des jolis "ping x pong x" sur chaque ligne.

   En fait:
   - l'écriture sur la sortie standard passe par un *buffer*
     (mémoire tampon) dont le contenu est affiché
     "de temps en temps" - au bon vouloir de votre système d'exploitation
   - par contre l'affichage sur la sortie d'erreur se fait dès que
     vous le demandez - avant l'instruction suivante.
   - quelle conséquence?
     Il vous arrivera d'afficher des messages d'erreurs pour déboguer
     votre programme. Oui c'est parfois pratique, même si ça ne
     remplace clairement pas les super outils gdb/ddd/valgrind!

     Par contre, imaginez le cas suivant (100% de chance que ça vous
     arrive in jour) :
        printf("avant f1...");
        f1();
        printf("apres f1...");
        f2();
     Vous voyez le premier message, puis "segmentation fault" !
     Logiquement, vous devriez chercher votre erreur dans f1?
     Et bien pas forcément; il est possible que l'erreur soit
     dans f2 mais que le message "apres f1" soit simplement resté
     dans le buffer avant le plantage.
     En cherchant une erreur au mauvais endroit, on peut y passer
     du temps...

    - donc pour des messages/traces "de debug", toujours utiliser
      la sortie d'erreur fprintf(stderr, ...)   !!!

    - solution de boyscout, ajouter '\n': printf("avant f1...\n");
      Généralement ceci force bien le vidage du buffer
      (flush, je vous laisse traduire). Mais ce n'est pas garanti, donc
      la sortie d'erreur est toujours une meilleure solution.

    - Une meilleure solution est d'explicitement demander le vidage du buffer
      par l'appel a la fonction 'fflush' qui permet de forcer l'ecriture
      immédiate des mémoires tampons associées a un ou tous les flux de sortie
      ouverts. C'est la seule maniere garantie par la norme d'obtenir ce
      resultat.
*/

int main(void)
{
    uint32_t n = 500;

    for (uint32_t i = 0; i < n; i++) {
        fprintf(stdout, "ping %d ", i);
        fprintf(stderr, "pong %d\n", i);
    }

    return EXIT_SUCCESS;
}

```


</details>
