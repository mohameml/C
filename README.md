# Table des matières
- [Documentation des ressources de la prépa C](#documentation-des-ressources-de-la-pr%C3%A9pa-c)
  - [Contenu d'un parcours](#contenu-dun-parcours)
    - [Exercices d'un parcours](#exercices-dun-parcours)
      - [Comment choisir un exercice ?](#comment-choisir-un-exercice-)
      - [Comment traiter un exercice ?](#comment-traiter-un-exercice-)
      - [J'ai terminé un exercice, je fais quoi ?](#jai-termin%C3%A9-cet-exercice-je-fais-quoi-)
      - [Progression au sein d'un parcours](#progression-au-sein-dun-parcours)
    - [Ensiquiquiz](#ensiquiquiz)
    - [TPs](#tps)
  - [Corrections](#corrections)
  - [Est-ce que j'avance assez vite ?](#est-ce-que-javance-assez-vite-)
- [De l'usage des outils à votre disposition](#de-lusage-des-outils-%C3%A0-votre-disposition)
  - [Dépôt Git](#d%C3%A9p%C3%B4t-git)
  - [Utilisation des tickets (issues)](#utilisation-des-tickets-issues)
    - [Pour organiser votre travail](#pour-organiser-votre-travail)
    - [Pour solliciter de l'aide](#pour-solliciter-de-laide)
    - [Entraide](#entraide)
    - [Remontée de bugs](#remont%C3%A9es-de-bug)
- [Travailler la prépa C sur son ordinateur personnel](#travailler-sur-son-ordinateur-personnel)

# Documentation des ressources de la prépa C

Bienvenue sur votre dépôt gitlab personnel.
Vous y trouverez tout le contenu des parcours dits de "base" et "avancé".
Ces contenus sont disponibles dans les répertoires du même nom.

Pour rappel, vous trouverez le "kit de démarrage" ainsi que les fiches de cours sur le site :
[http://formationc.pages.ensimag.fr/prepa/prof](http://formationc.pages.ensimag.fr/prepa/prof)

## Contenu d'un parcours

Un parcours contient :
- un ensemble d'exercices de programmation ;
- un quiz interactif ;
- un ensemble de TPs de synthèse.

### Exercices d'un parcours

Le sommaire des exercices d'un parcours se trouve :
- dans [./base/sommaire.md](./base/sommaire.md) pour le parcours de base ;
- dans [./avance/sommaire.md](./avance/sommaire.md) pour le parcours avancé.

Les exercices y sont triés par compétences traitées. La couleur du
badge d'un exercice indique sa difficulté :
![facile](http://img.shields.io/badge/facile-0-brightgreen.svg),
![moyen](http://img.shields.io/badge/moyen-0-yellow.svg),
![difficile](http://img.shields.io/badge/difficile-0-red.svg)

Le sommaire contient aussi un niveau de maîtrise par compétence,
indiqué par une petite barre de progression en face de chacune d'elle,
et un niveau de maîtrise par exercice, indiqué par un chiffre sur le
badge de l'exercice.

#### Comment choisir un exercice ?

Le sommaire d'un parcours présente la liste des exercices sous la
forme d'un tableau organisé par compétences. Pour chaque compétence
d'un parcours, on retrouve en face la liste des exercices
associés. Bien entendu, un exercice traite souvent de plusieurs
compétences, aussi vous retrouverez certains exercices sur plusieurs lignes
du sommaire.

Vous êtes libre de traiter les exercices dans l'ordre qui vous plaît.

#### Comment traiter un exercice ?

En cliquant sur un exercice dans le sommaire, vous arrivez sur la page
gitlab de l'exercice, qui contient entre autres un fichier
`README.md`. Ce fichier contient toujours :
- l'énoncé de l'exercice ;
- l'emplacement où trouver les sources de départ dans votre dépôt
  gitlab personnel ;
- la liste des compétences abordées par l'exercice ;
- des indices, cachés par défaut mais que vous pouvez afficher en
  cliquant au bon endroit ;
- la correction, cachée elle aussi par défaut.

Cette correction s'affiche en ligne, mais nous vous donnons aussi
accès à un dépôt git séparé contenant toutes les corrections de tous
les exercices de la prépa C (voir plus bas) pour que vous puissiez
jouer avec directement.

#### J'ai terminé cet exercice, je fais quoi ?

Quand vous avez terminé un exercice, vous devez valider votre
progression en tapant

```
make progress
```

depuis le répertoire de l'exercice.

Vous devriez voir s'afficher un petit quiz interactif vous permettant
d'indiquer votre maîtrise de l'exercice que vous venez de terminer, et
éventuellement mettre à jour la maîtrise des compétences qu'il
traitait.

#### Progression au sein d'un parcours

Si vous validez chaque exercice correctement, vous devriez voir le sommaire
du parcours afficher votre progression sous la forme de la barre de
progression des compétences, et du chiffre affiché sur le badge des
exercices traités.

Si rien n'est mis à jour, c'est certainement que vous ne tapez pas
`make progress` pour valider un exercice ! (ou que notre intelligence
artificielle qui gère tout ça est en grève).

### Ensiquiquiz

Le répertoire `quiz` contient un petit programme qui lance des quiz
interactifs en ligne de commande. Pour jouer avec, lancez :

```
./ensiquiquiz
```

Chaque parcours vient avec sa propre base de données de questions, qui
sont tirées dans un ordre prédéfini. Par défaut, `ensiquiquiz` ne vous
proposera que des questions pour lesquelles vous n'avez pas encore
obtenu le score maximal.

Il existe des options pour changer ce comportement par défaut (`./ensiquiquiz --help` pour plus d'infos).

### TPs

Le répertoire `TPs` contient des TPs de synthèse d'un parcours. Vous
pouvez voir ça comme un mini-projet, donc au temps de développement
bien plus conséquent que la plupart des petits exercices du répertoire `exercices`.

## Corrections

La correction des exercices est disponible dans un dépôt git séparé que vous
pouvez trouver ici :

https://gitlab.ensimag.fr/formationc/prepa/ensimag/correction

## Est-ce que j'avance assez vite ?

Au terme de la "semaine intensive de C" (c'est à dire des 15 premières heures de TP) d'introduction au C, on estime
que vous devriez avoir traité et compris l'exercice [listes](base/exercices/listes) du parcours
de base, ainsi que le TP [Alibaba](base/TPs/alibaba/).
Vous êtes libres d'emprunter le chemin que vous souhaitez pour atteindre
ce premier objectif.

Si cette liberté vous effraie, nous vous proposons l'ordre suivant
pour traiter les premiers exercices de la prépa C :

1. capitaine
1. papous
1. diviseurs
1. do-while
1. somme-pairs
1. safari
1. somme-impairs
1. palindrome
1. rationnels
1. module-tableaux
1. liste
1. TP Alibaba

# De l'usage des outils à votre disposition

En plus de vous former au C, vous aurez l'occasion de vous initier à l'utilisation de Gitlab.
Voici quelques conseils d'utilisation basique.

## Dépôt Git

La fonctionnalité de base de GitLab, c'est de fournir un dépôt Git par projet.
Vous disposez d'un projet Gitlab à vous.
Donc, utilisez votre dépôt Git pour versionner votre code.
Concrètement, ca vous permet de garder une trace de l'évolution de vos développements.
Voici un ensemble minimaliste de commandes que vous pourrez utiliser :
* `git status` pour connaître l'état de votre dépôt
* `git add <fichiers>` pour ajouter des nouveaux fichiers dans votre dépôt ou mettre à jour des fichiers déjà dans le dépôt
* `git commit -m "Message explicitant les changements"` pour valider et enregistrer plusieurs changements dans votre dépôt local
* `git push` pour envoyer les changements vers le dépôt distant (sur le serveur Gitlab)

Vous trouverez plus de ressources à propos de Git sur l'[Ensiwiki](https://ensiwiki.ensimag.fr/index.php?title=Git).

## Utilisation des tickets (issues)

La plateforme gitlab fournit un système de ticket intuitif qui peut être utilisé dans de nombreux contextes.
Les plus courageux pourront parcourir la [documentation gitlab](https://gitlab.ensimag.fr/help/user/project/issues/index.md).

Vous trouverez ci-dessous quelques usages utiles.

### Pour organiser votre travail

En complément des sommaires (cartes des compétences), vous pouvez utiliser des issues pour organiser votre apprentissage.
Vous pourrez ainsi vous fixer des objectifs ou juste vous faire des pense-bêtes (TODO list).
De quoi faire un premier pas vers les méthodes agiles.

### Pour solliciter de l'aide

Depuis vos issues, vous pouvez également demander un coup de main à un autre utilisateur.
En écrivant `@toto` dans le titre ou le corps du message, l'utilisateur 'toto' recevra une notification.
Cela marche aussi pour solliciter des groupes d'utilisateurs.
Pour vous faciliter la vie, on vous fournit un template qui ressemble au message ci-dessous.
Pour l'utiliser, il suffit à la création d'une issue de cliquer sur *Choose a template* et de choisir le template **Aide**.

```
@formationc/prepa
Parcours : base
Exercice : papou

Ma description super limpide du problème qui empêche de compiler le C.

État : :grimacing: (ou :confused: ou :sob: ou :rage: ...)
Ma localisation : E103 poste xxx
```

En complétant dûment ce template, il est probable qu'un enseignant arrive près de vous pour vous apporter son aide en étant déjà au courant de votre problème.
Attention, selon une loi statistique bien connue des enseignants, la probabilité décroît fortement en fonction du nombre de sollicitations.

### Entraide

Selon une autre loi pragmatique bien connue des étudiants, on ne crache pas sur l'aide rapide d'un collègue quand le prof tarde à venir.
Pour gérer ce principe, on a créé le sous-groupe d'entraide.
Les étudiants prêts à donner de leur temps pour aider *bénévolement* leurs collègues doivent se signaler auprès des enseignants (@formationc/prepa pour ceux qui ne suivent pas).

Ainsi pour solliciter l'aide des copains, il suffira d'ajouter @formationc/prepa/ensimag/entraide quelque part dans son message.

### Remontées de bug
Si vous constatez des bugs/typos ou voyez des améliorations possibles pour cet enseignement, n'hésitez pas à nous en faire part en déposant un ticket dans le projet /formationc/prepa/prof.

# Travailler sur son ordinateur personnel

Pour pouvoir travailler la prépa C sur votre environnement de travail personnel, il vous faut :
- GNU make ;
- un debugger (gdb par exemple) ;
- un compilateur C: les `Makefile` fournis compilent avec `clang` par défaut, mais il vous suffira de les modifier si vous en utilisez un autre ;
- python 3, avec le module `pyyaml` d'installé.

Les ressources de la prépa C ont été conçues pour être utilisées à l'Ensimag.
Certains exercices et TPs fournissent des fichiers objet (`.o`) qui ont été compilés pour fonctionner sur les machines de l'école.
Nous ne fournirons pas d'autres versions de ces fichiers objet, mais ce n'est pas bloquant pour travailler: la plupart du temps, ces `.o` sont distribués pour que vous puissiez tester votre implémentation.

Vous pouvez aussi bien entendu vous connecter sur les machines de l'école depuis l'extérieur. Référez-vous pour ça à la documentation disponible sur l'intranet : [ici](http://intranet.ensimag.grenoble-inp.fr/fr/informatique/wifi-vpn-et-acces-distant-vpn?ksession=a75820b6-66cf-42b8-b14d-38fc8d42f400)

Les enseignants n'assureront pas le support pour ce qui est du déploiement de l'environnement prépa C sur vos machines personnelles. Par contre, n'hésitez pas à centraliser les infos à ce sujet sur un ticket gitlab et à demander l'aide de vos collègues.
