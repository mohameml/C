# Jeu Puissance X

![Plateau du jeu Puissance 4](puissance4.jpg)

## Présentation

Le but de cet exercice est de se familiariser avec quelques points de base
du langage C, à travers la mise en oeuvre d’un jeu de puissance X, une
généralisation du jeu [Puissance 4](https://fr.wikipedia.org/wiki/Puissance_4)
étendu à _N_ lignes, _M_ colonnes et dont l’objectif est d’aligner _X_ pions de
même couleur en ligne, colonne ou diagonale.

Les objectifs de ce sujet, du point de vue du langage C, sont les suivants :

* Utilisation du préprocesseur ;
* Utilisation des arguments `argc` et `argv` de la fonction `main` ;
* Programmation modulaire ;
* Tableaux de dimension variable, pointeurs de pointeurs ;
* Ecriture dans un fichier ;
* Utilisation des types C99 ;
* Utilisation de l’assertion pour la gestion des erreurs ;
* Utilisation des fonctions de manipulation de chaines de caractères (`strcmp`, `strtol`, ...) ;
* Utilisation de `gdb` et de `valgrind`.

L’appel au programme pourra s'effectuer de 2 façons :

* soit sans arguments : la saisie de tous les paramètres sera alors demandée
par le programme à l'utilisateur
* soit avec arguments : l'utilisateur passe tous les paramètres du programme
en ligne de commandes. Il vous est demandé de vérifier que le nombre et le type
des arguments de la ligne de commandes sont corrects. Dans le cas contraire,
votre programme devra afficher un message d’aide avec le format d'appel attendu.
Cette aide pourra aussi être consultée en appelant votre programme avec l’option `-h`.

Nous vous demandons de privilégier les types C99 pour vos variables : `uint32_t`, `int16_t`, `bool`, ...
Par ailleurs, il vous est demandé d'utiliser le préprocesseur pour _versionner_ le programme.

## Mise en oeuvre du jeu puissance X

### Objectifs

Le programme puissance X devra permettre de paramétrer les données suivantes :

* nombre de lignes du plateau de jeu ;
* nombre de colonnes du plateau de jeu ;
* nombre de pions à aligner pour gagner (le _X_ de puissance X) ;
* mode de jeu : Humain/Humain, Humain/Ordinateur, Ordinateur/Ordinateur.

Ces paramètres principaux du jeu seront stockés dans une seule structure de données.

Les paramètres pourront être donnés en arguments de l’appel du programme en ligne de commandes :

    ./puissanceX 10 20 5 HH

Cet exemple lancera le programme avec 10 lignes, 20 colonnes, 5 pions à aligner
en mode de jeu Humain/Humain. Dans ce type d’appel, le mode de jeu sera renseigné
de la façon suivante :

* soit `HH` : Humain / Humain ;
* soit `HO` : Humain / Ordinateur ;
* soit `OO` : Ordinateur / Ordinateur.

Si aucun paramètre n’est passé en arguments de la ligne de commande ou si le
nombre d’arguments attendus est incomplet, le programme puissance X demandera
à l’utilisateur de saisir l’intégralité des paramètres.

### Directives de programmation

#### Programmation modulaire

Le programme puissance X comportera au minimum 4 modules :

* un module `plateau` qui contiendra l'ensemble des fonctionnalités liées au plateau de jeu ;
* un module `jeu` qui contiendra l'ensemble des fonctionnalités liées aux règles du jeu puissance X ;
* un module `ui` qui contiendra les fonctionnalités liées à l'interface utilisateur,
contenant les fonctions liées à l'affichage et la saisie des données ;
* un module `main`, point d'entrée du programme, qui utilisera les 3 autres modules.

Chaque module sera découpé en fonctions élémentaires permettant une programmation simple,
structurée et très lisible du programme.

#### Allocation dynamique du plateau de jeu

Pour mettre en oeuvre le plateau de jeu à dimensions variables, une première version
pourra utiliser les tableaux VLA (Variable-Length Arrays) définis en C99.
Mais la version finale du programme devra utiliser une allocation dynamique
à base de pointeurs de pointeurs permettant de manipuler facilement le plateau
de jeu avec la syntaxe des tableaux pour le reste des traitements.
Les erreurs d’allocations seront traitées par assertions.
Il vous est demandé d'écrire 2 variantes pour cette allocation dynamique :

* une première variante où la fonction d'allocation du plateau de jeu retourne
le plateau alloué ;
* une deuxième variante où la fonction d'allocation prend en paramètre le plateau
à allouer.

#### Moteur de jeu

Pour le jeu de l’humain, on vérifiera que le coup est valable.
Sinon, on demandera à l’utilisateur de proposer un autre coup jusqu’à obtenir
un coup valable.

Pour le jeu de l’ordinateur, on implémentera dans un premier temps un algorithme
très simple :

* on choisit une colonne du plateau au hasard à l'aide d'un tirage aléatoire.
On pourra pour ce faire utiliser la fonction `random()`de la bibliothèque standard C.
* on vérifie que le coup est possible, c'est-à-dire que la colonne choisie n'est
pas pleine. Sinon, on recommence jusqu'à tomber sur une colonne non pleine.

Pour les coups de l’ordinateur et de l’humain, une même fonction permettra de
vérifier si l’alignement du nombre de pions désiré est obtenu.

Le jeu s’arrête lorsque l’alignement de X pions est obtenu par un des joueurs
ou lorsque le plateau de jeu est plein sans qu’un vainqueur ne soit désigné.

#### Affichage du jeu

L’affichage en mode console représentera le plateau de jeu de façon très simple.
Par exemple :

    0 0 0 0 0 0 0
    0 0 0 0 0 0 0
    1 2 1 0 0 1 1
    2 1 2 1 2 1 2

représente un plateau de jeu avec 4 lignes, 7 colonnes.
Le chiffre 0 représente une case vide, 1 représente un pion du joueur 1
et 2 un pion du joueur 2.

Le programme devra générer, en plus de l’affichage en mode console,
un fichier de log `puissanceX.log` retraçant le déroulement du jeu étape par étape.

#### Débogage : gdb/ddd et valgrind

Le debugger `gdb/ddd` sera utilisé pour tracer les erreurs du programme.
`valgrind` sera aussi utilisé pour vérifier l’allocation correcte des données
dynamiques du programme et l'absence de fuite mémoire.

## Extensions possibles

### Bibliothèques statiques et dynamiques

Mettre en oeuvre une implémentation du programme sous forme de bibliothèque
 statique puis d'une bibliothèque dynamique (cf. TD Cycle de Vide). Compléter le
 Makefile pour générer également ces 2 formes de librairies.

### Moteur de jeu ordinateur

Mettre en œuvre une IA pour le jeu de l’ordinateur de type
[minmax](http://fr.wikipedia.org/wiki/Algorithme_minimax).

### Interface homme machine

Option 1 : Mettre en œuvre la librairie
[readline](http://tiswww.case.edu/php/chet/readline/rltop.html) pour gérer le
rafraichissement de l'affichage du plateau de jeu.

Option 2 : Mettre en œuvre une interface graphique avec la librairie
[SDL](http://www.libsdl.org)

# Compétences


# Difficulté

:star:
