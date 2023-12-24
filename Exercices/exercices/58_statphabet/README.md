# Enoncé

Cet exercice va vous donner l'occasion d'analyser la prose de poêtes
français parmi les plus talentueux de notre ère (ici, [Annie
Cordy](https://fr.wikipedia.org/wiki/Annie_Cordy) et [Carlos
Dolto](https://fr.wikipedia.org/wiki/Carlos_(chanteur))).

On vous demande d'écrire un programme qui prend un fichier texte en
argument de la ligne de commandes, l'analyse et affiche en sortie le
nombre de fois qu'apparaissent chacune des lettres de l'alphabet dans
ladite oeuvre.

Par exemple, `./statphabet tatayoyo.txt` doit afficher un rapport de
la forme :

```
a: 111
b: 12
c: 13
d: 43
e: 92
f: 10
g: 26
h: 7
i: 56
j: 10
k: 0
l: 32
m: 57
n: 64
o: 70
p: 13
q: 16
r: 23
s: 60
t: 61
u: 55
v: 3
w: 0
x: 7
y: 27
z: 0
caracteres speciaux: 318
```

Vous noterez que tata yoyo ne contient aucune occurrence du caractère
`'k'`, au contraire du titre "cho ka ka o" qui fait monter ce compteur
en flèche grâce au fameux "ki ki ki le petit kiwi".

Votre analyse ne doit pas être sensible à la case : on comptera
indifféremment `'a'` et `'A'` comme étant une occurrence de a.

On considère que tout caractère non alphabétique (a-z ou A-Z) comme
étant un caractère spécial.

Vous pourrez tester votre implémentation sur les fichiers
`tatayoyo.txt` et `papayou.txt` fournis, ou tout autre composition de
votre choix, y compris le répertoire de [Nana
Mouskouri](https://fr.wikipedia.org/wiki/Nana_Mouskouri).

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/base/statphabet/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

- man ascii
- Aller voir les fonctions : `isalpha` et `islower`
- Que vaut 'c' - 'b' ?
</details>

# Compétences

* Champs de bits
* Caractères
* Opérateurs d'incrémentation
* Codage ASCII
* Ouverture de fichier
* Fermeture de fichier
* Lecture caractère par caractère

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: statphabet

.PHONY: clean
clean:
	rm -f *~ *.o statphabet

```

#### Corrigé du fichier statphabet.c

```c
/*
    Enoncé :

    Cet exercice va vous donner l'occasion d'analyser la prose de poêtes français
    parmi les plus talentueux de notre ère (ici, Annie Cordy et Carlos Dolto).

    On vous demande d'écrire un programme qui prend un fichier texte en argument
    de la ligne de commandes, l'analyse et affiche en sortie le nombre de fois
    qu'apparaissent chacune des lettres de l'alphabet dans ladite oeuvre.

    Par exemple, ./statphabet tatayoyo.txt doit afficher un rapport de la forme :

    a: 110
    b: 12
    c: 13
    d: 43
    e: 89
    f: 10
    g: 26
    h: 7
    i: 56
    j: 10
    k: 0
    l: 32
    m: 57
    n: 64
    o: 70
    p: 13
    q: 16
    r: 23
    s: 61
    t: 61
    u: 55
    v: 3
    w: 0
    x: 7
    y: 27
    z: 0
    caracteres speciaux: 326

    Vous noterez que tata yoyo ne contient aucune occurrence du caractère 'k', au
    contraire du titre "cho ka ka o" qui fait monter ce compteur en flèche grâce
    au fameux "ki ki ki le petit kiwi".

    Votre analyse ne doit pas être sensible à la case : on comptera indifféremment
    'a' et 'A' comme étant une occurrence de a.

    On considère que tout caractère non alphabétique (a-z ou A-Z) comme étant un
    caractère spécial.

    Vous pourrez tester votre implémentation sur les fichiers tatayoyo.txt et
    papayou.txt fournis, ou tout autre composition de votre choix, y compris le
    répertoire de Nana Mouskouri.

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    /*
        Affiche un message d'erreur si l'utilisateur oublie l'argument
        à passer en ligne de commandes.
    */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s fichier.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* On récupère le nom du fichier à ouvrir sur la ligne de commandes. */
    const char *texte = argv[1];

    /*
        On va compter les caractères dits "spéciaux", c'est-à-dire
        tous ceux qui ne sont pas alpha (autres que a-z ou A-Z).
    */
    uint64_t caracteres_speciaux = 0;

    /* Ce tableau compte le nombre d'occurrences de lettres dans le fichier. */
    uint64_t alphabet[26] = { 0 };


    /* On ouvre le fichier en lecture. */
    FILE *fichier_texte = fopen(texte, "r");

    /* Tant qu'on n'a pas atteint la fin du fichier ... */
    while(!feof(fichier_texte)) {
        /* ... on lit un caractère depuis le fichier ... */
        char c;
        fread(&c, 1, 1, fichier_texte);

        /* ... si ce caractère est une lettre ... */
        if (isalpha(c)) {
            /*
                ... alors soit c'est une majuscule, soit une minuscule.
                Pour savoir quelle case du tableau alphabet incrémenter,
                on s'appuie sur le code ASCII du caractère (man ascii pour
                plus de détails).

                Les minuscules ont un code ASCII croissant, qui part de 'a' jusqu'à 'z'.
                Les majuscules ont aussi un code ASCII croissant, de 'A' jusqu'à 'Z'.

                On utilise cette propriété pour déduire l'indice du tableau
                alphabet à incrémenter : si c est une minuscule, on incrémente la case
                d'indice c - 'a'.

                Par exemple, si c vaut 'a', on incrémentera la case alphabet[0],
                si c vaut 'b', on incrémentera alphabet['b' - 'a'] == alphabet[1],
                et ainsi de suite.

                Même raisonnement pour les majuscules.

                islower() retourne True si le caractère passé en paramètre
                est une minuscule.
            */
            char preums = islower(c) ? 'a' : 'A';
            alphabet[c - preums]++;
        } else {
            /*
                ... et si ce n'est pas une lettre, on incrémente le compteur
                des caractères spéciaux!
            */
            caracteres_speciaux++;
        }
    }
    /* On n'oublie pas de fermer le fichier, sinon valgrind dit que notre programme fuit. */
    fclose(fichier_texte);

    /* Enfin, on affiche les statistiques. */
    for (size_t i = 0; i < 26; i++) {
        printf("%c: %llu\n", (char)(i + 'a'), alphabet[i]);
    }
    printf("caracteres speciaux: %llu\n", caracteres_speciaux);


    return EXIT_SUCCESS;
}

```


</details>
