# Enoncé

La société :dollar: BigBucks :dollar: prépare un plan social
d'envergure.  Afin de mieux cibler qui seront les victimes, elle
entame la saisie informatique du profil de ses salariés.

L'appat du gain vous oblige à implémenter un prototype de module de
gestion des salariés. Le cahier des charges de ce module est décrit
dans le fichier `salarie.h`.

En particulier, il vous incombe de définir une structure de données
représentant un salarié de l'entreprise, avec les contraintes
suivantes :

elle devra contenir, dans cet ordre :
- son prénom sous la forme d'une chaine de caractères de longueur max
  16 ;
- son nom sous la forme d'une chaine de caractères de longueur max 32
  ;
- son age, sous la forme d'un entier non signé 8 bits ;
- son ancienneté dans l'entreprise, sous la forme d'un entier
  non-signé 8 bits ;
- son salaire mensuel, sous la forme d'un entier non signé 32 bits.

Le module que vous implémenterez comprend aussi des fonctions
d'allocation, initialisation et libération d'un salarié.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/bigbucks/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Si le prénom et le nom ne s'affichent pas correctement, c'est que
  vous avez "mal" déclaré ces champs dans votre structure. Prenez le
  temps de lire les commentaires de la fonction `afficher_salarie()`
  pour comprendre ce qu'on attend de vous.
* Tout s'affiche bien, sauf le salaire ? Jetez un oeil à
  https://fr.wikipedia.org/wiki/Alignement_en_m%C3%A9moire

</details>

# Compétences

* Structures
* Transtypage de types avancés
* Passage de l'adresse d'une variable
* Opérateur adresse de
* Opérateur d'indirection
* Opérations arithmétiques sur les pointeurs
* Fonction taille mémoire d'un type de donnée
* Allocation de mémoire dynamique type de donnée simple
* Libération de mémoire
* Pointeurs de structures
* Pointeurs de pointeurs

# Difficulté

:star: :star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: bigbucks

salarie.o: salarie.c salarie.h

bigbucks: salarie.o bigbucks.o

.PHONY: clean
clean:
	rm -f *~ *.o bigbucks

```

#### Corrigé du fichier bigbucks.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "salarie.h"

void afficher_salarie(void *sal) {
    /*
	Version qui n'utilise pas votre définition de struct salarie,
	mais s'appuie sur le cahier des charges, en allant lire directement
	en mémoire depuis l'adresse de base de l'objet "sal" passé en paramètre.
    */

    /*
	En première position dans la structure, on doit retrouver
	une chaine de caractères de longueur 16.
    */
    const char *prenom = sal;

    /*
	Le nom vient en 2e position dans la structure, il doit donc
	se trouver 16 octets après l'adresse de base.
    */
    const char *nom = sal + 16;

    /*
	Ensuite vient l'age, qui se trouve après le prénom (16 octets)
	et le nom (32 octets). L'age est codé sur 1 octet.
    */
    uint8_t age = *(uint8_t *)(sal + 16 + 32);

    /*
	Ensuite vient l'ancienneté, qui se trouve après le prénom (16 octets),
	le nom (32 octets) et l'age (1 octet). L'ancienneté est codée sur 1 octet.
    */
    uint8_t anciennete = *(uint8_t *)(sal + 16 + 32 + 1);

    /*
	Enfin vient le salaire, qui se trouve après le prénom (16 octets),
	le nom (32 octets), l'age (1 octet) et l'ancienneté (1 octet).

	Attention, chaud cacao : on avance de deux octets supplémentaires,
	parce qu'un mot de 4 octets commence toujours à une adresse
	multiple de 4 octets. Voir le commentaire de la fonction allouer_salarie()
	dans la correction pour plus de détails.

	Le salaire est codé sur 4 octets.
    */
    uint32_t salaire = *(uint32_t *)(sal + 16 + 32 + 1 + 1 + 2);

    printf("%s %s a %u ans.\n", prenom, nom, age);
    printf("Il est dans l'entreprise depuis %u années et gagne %u euros par mois.\n",
	   anciennete, salaire);
}

int main(void)
{
    struct salarie *s1, *s2;

    /*
	On créé le premier salarié. Il est dans l'entreprise depuis
	longtemps, son salaire est mirobolant!

	Ici on sépare l'allocation de l'initialisation de la structure.
    */
    s1 = allouer_salarie();
    init_salarie(s1, "Donald", "Trump", 70, 70, -1);
    afficher_salarie(s1);

    /*
	Un deuxième salarié, plus modeste.

	Ici, on utilise creer_salarie() qui effectue l'allocation
	ET l'initialisation du salarié.
    */
    creer_salarie(&s2, "John", "Doe", 34, 10, 2500);
    afficher_salarie(s2);

    /* On met la clé sous la porte, tout le monde passe à la trappe! */
    plan_social(&s1);
    plan_social(&s2);

    return EXIT_SUCCESS;
}

```

#### Corrigé du fichier salarie.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "salarie.h"


struct salarie {
    /* Le prénom, sous forme d'un tableau de 16 caractères. */
    char prenom[16];

    /* Le nom, sous forme d'un tableau de 32 caractères. */
    char nom[32];

    /*
        Il est à noter qu'on aurait pu définir les champs nom et prenom
        comme suit :
        char *prenom;
        char *nom;

        Dans ce cas, la structure salarie ne contient plus les 16 caractères
        du prenom et les 32 caractères du nom directement, mais deux pointeurs :
        un vers la chaine de caractères contenant le prenom, l'autre vers celle
        contenant le prénom.

        Du coup, en terme d'organisation en mémoire, les deux solutions ne sont pas
        équivalentes, et seule celle donnée dans ce corrigé est compatible avec la
        fonction afficher_salarie() donnée dans le fichier bigbuck.c.
     */
    uint8_t age;
    uint8_t anciennete;
    uint32_t salaire;
};

/* Alloue et retourne un struct salarie. */
struct salarie *allouer_salarie(void) {
    /*
        Avec notre implémentation, sizeof(struct salarie) =
            16 * sizeof(char)
            + 32 * sizeof(char)
            + sizeof(uint8_t)
            + sizeof(uint8_t)
            + sizeof(uint32_t)
            = 54

        Pourtant, si vous executez :
        printf("%d\n", sizeof(struct salarie));

        56 s'affiche! (et non 54)

        Il existe en pratique un "trou" de 2 octets entre le champ ancienneté
        et le champ salaire, parce qu'un mot de 4 octets ne peut être stocké
        qu'à une adresse multiple de 4.

        De la même manière, si on avait voulu stocker une variable de type
        uint64_t (8 octets), elle aurait été stockée en mémoire à une adresse
        multiple de 8.

        C'est ce qu'on appelle les contraintes d'alignement.
    */
    return malloc(sizeof(struct salarie));
}

/*
    Initialise le salarié passé en paramètre.
    Le salarié s a déjà été alloué avant l'appel
    à init_salarie().
*/
void init_salarie(struct salarie *s,
                  const char *prenom,
                  const char *nom,
                  uint8_t age,
                  uint8_t anciennete,
                  uint32_t salaire) {
    s->age = age;
    s->anciennete = anciennete;
    s->salaire = salaire;
    /*
        Pas d'allocation nécessaire pour s->prenom et s->nom, puisque la place
        qu'elles occupent a été réservée par allouer_salarie().
    */
    strncpy(s->prenom, prenom, 16);
    strncpy(s->nom, nom, 32);
}

/* Effectue l'allocation ET l'initialisation du salarie passé en paramètre. */
void creer_salarie(struct salarie **s,
                   const char *prenom,
                   const char *nom,
                   uint8_t age,
                   uint8_t anciennete,
                   uint32_t salaire) {
    /*
        Cette fonction va modifier le paramètre de type struct salarie *,
        puisqu'elle va changer sa valeur pour qu'elle représente l'adresse
        d'un struct salarie fraichement alloué.

        Comme on souhaite modifier ce paramètre, on passe son adresse à la fonction,
        et on se retrouve donc à travailler sur un struct salarie ** (l'adresse
        d'un struct salarie *).
    */
    *s = allouer_salarie();
    init_salarie(*s, prenom, nom, age, anciennete, salaire);
}

/*
    Libère la mémoire associée au salarié passé en paramètre.
    En sortie, s doit valoir NULL.
*/
void plan_social(struct salarie **s) {
    /*
        Même remarque qu'au dessus : on va modifier le paramètre s ici,
        qui est de type struct salarie *. On passe donc son adresse et on se
        retrouve avec un struct salarie **.
    */
    free(*s);
    *s = NULL;
}


```

#### Corrigé du fichier salarie.h

```c
#ifndef SALARIE_H
#define SALARIE_H

/*
    Structure de données représentant un salarié.
    Elle devra contenir, dans cet ordre :
    - son prénom sous la forme d'une chaine de caractères de longueur max 16 ;
    - son nom sous la forme d'une chaine de caractères de longueur max 32 ;
    - son age, sous la forme d'un entier non signé 8 bits ;
    - son ancienneté dans l'entreprise, sous la forme d'un entier non-signé 8 bits ;
    - son salaire mensuel, sous la forme d'un entier non signé 32 bits.
*/
struct salarie;

/* Alloue et retourne un struct salarie. */
extern struct salarie *allouer_salarie(void);

/*
    Initialise le salarié passé en paramètre.
    Le salarié s a déjà été alloué avant l'appel
    à init_salarie().
*/
extern void init_salarie(struct salarie *s,
                         const char *prenom,
                         const char *nom,
                         uint8_t age,
                         uint8_t anciennete,
                         uint32_t salaire);

/* Effectue l'allocation ET l'initialisation du salarie passé en paramètre. */
extern void creer_salarie(struct salarie **s,
                          const char *prenom,
                          const char *nom,
                          uint8_t age,
                          uint8_t anciennete,
                          uint32_t salaire);

/*
    Libère la mémoire associée au salarié passé en paramètre.
    En sortie, s doit valoir NULL.
*/
extern void plan_social(struct salarie **s);

#endif /* SALARIE_H */

```


</details>
