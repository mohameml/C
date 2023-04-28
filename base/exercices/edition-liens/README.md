# Enoncé

L'objectif de cet exercice est de compiler à la main (sans Makefile)
un programme C composé de plusieurs modules: le programme principal,
`main`, appelle une fonction dont l'implémentation est donnée dans un
fichier séparé (`mon_super_module.c`).

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/edition-liens/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* L'option `-c` permet de générer un fichier objet (.o) à partir d'un
  fichier source (.c) ;
* Pour générer un exécutable, l'ensemble des fichiers objets doivent
  être "liés" ensemble.
</details>

# Compétences

* Option fichier objet
* Option fichier exécutable
* Edition de liens
* Découpage d'un programme en modules

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier main.c

```c
#include <stdlib.h>

#include "mon_super_module.h"

/*
   == version complete, compilation separée + édition de liens

   Si on compile main.c seul, par exemple avec la commande:

   gcc -Wall -Wextra -std=c99 main.c

   on obtient une erreur de référence indéfinie vers la fonction
   mon_super_message_de_reussite(). Le code binaire de cette fonction se
   trouve dans mon_super_module.o, qu'on obtient par compilation du
   fichier source mon_super_module.c (notez bien l'option -c):

   gcc -Wall -Wextra -std=c99 -c mon_super_module.c

   On génère de la même façon main.o à partir de main.c:

   gcc -Wall -Wextra -std=c99 -c main.c

   Il ne reste plus qu'à lier les deux fichiers objets pour générer un
   exécutable:

   gcc -Wall -Wextra -std=c99 mon_super_module.o main.o -o maino


   == version plus simple

   Une autre solution (que vous avez peut-être trouvé) est simplement:

   gcc -Wall -Wextra -std=c99 mon_super_module.c main.c -o main

   Ca marche très bien, et c'est facile. Alors pourquoi s'embêter?
   En fait cette solution compile systématiquement TOUS les fichiers fournis.
   Avec cet exemple, aucun pb.
   Essayez maintenant avec le noyau Linux (écrit en C, oui oui): si vous
   modifiez un ";" vous devrez tout recompiler!
   La première solution, bien plus complète, est donc indispensable
   dès que vous ferez un projet un peu complexe que nos petits exercices.

   (Sur le fond, les notions de compilation séparée et d'édition de liens
   sont très importantes!
   Inconvénient: vous aurez moins de temps pour boire des kfés pendant la
   compilation de votre noyau...)

*/

int main(void)
{
    mon_super_message_de_reussite();
    return EXIT_SUCCESS;
}

```

#### Corrigé du fichier mon_super_module.c

```c
#include <stdio.h>

#include "mon_super_module.h"

void mon_super_message_de_reussite(void)
{
    printf("F*ck yeah!\n");
}

```

#### Corrigé du fichier mon_super_module.h

```c
#ifndef _MON_SUPER_MODULE_H_
#define _MON_SUPER_MODULE_H_

extern void mon_super_message_de_reussite(void);

#endif /* _MON_SUPER_MODULE_H_ */

```


</details>
