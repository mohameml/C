# Enoncé

Au menu de cet exercice: lecture par ligne dans un fichier, des
entrées formattées depuis une chaine, des écritures et lectures dans
un fichier binaire, de la gestion des paramètres `argc`, `argv`.

Luke Skywalker a disparu mais pas que lui. D'autres Jedi sont aussi
cachés dans la galaxie. Heureusement, r2d2 a conservé un fichier
(`r2.txt`) contenant les fiches de ces Jedi.

Votre mission, si vous l'acceptez, est de convertir ce fichier en
binaire afin de le protéger à minima et de permettre un accès direct
aux fiches à partir de l'Identifiant Spatial Jedi (`isj`, que l'on
peut voir comme la position dans le fichier binaire généré).

Votre mission est aussi de fournir une fonction de recherche d'une
fiche Jedi dans ce fichier binaire.

En cas de problème, le département d'état niera toute implication dans
cette opération.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/jedi/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Regardez la documentation sur les paramètres `argc`, `argv` (et `atoi`
  pour la conversion en entier)
* Regardez la documentation des fonctions `fopen`, `fgets`, `sscanf`,
  `fscanf`, `fseek`, `fwrite`
* Lecture d'une fiche : utiliser `sscanf` (solution 1) ou `fscanf`
  (solution 2) pour affecter un par un chaque champ de la structure
  `struct jedi`
* Ecriture dans le fichier binaire : positionnez-vous dans le fichier
  en vous décalant, depuis le début de fichier, de isj * la taille de
  `struct jedi`

</details>

# Compétences

* Fonctions de conversion d'une chaine de caractères en entier
* Ouverture de fichier
* Fermeture de fichier
* Ecriture dans un fichier binaire
* Lecture par ligne
* Entrées formatées depuis un fichier
* Entrées formatées depuis une chaine
* Passage de paramètres au programme principal
* Déplacement au sein d'un fichier

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
# Activer la ligne suivante pour tester la solution 2 avec fscanf
#CFLAGS+=-DSOL2

all: jedi

.PHONY: clean
clean:
	rm -f *~ *.o jedi

```

#### Corrigé du fichier jedi.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SIZE 20     // taille maximale d'un champ de caractères : nom, prénom, planète

/* Structure d'une fiche de données Jedi */
struct jedi {
    uint32_t    isj;		    // Identifiant Spatial Jedi : identifiant unique, c'est l'INE des Jedi
    char        nom[SIZE];
    char        prenom[SIZE];
    uint16_t    age;
    float       taille;
    char        planete[SIZE];
};

/*
    Affiche tous les champs de la fiche Jedi passée en paramètre.
    Fonction utilisée par print_isj.
*/
void print_jedi(struct jedi *jedi)
{
    /* A compléter */
    if (jedi->isj == 0) {
	printf("Jedi n° %u non trouvé\n", jedi->isj);
    } else {
	printf("Fiche Jedi n° %u :\n", jedi->isj);
	printf("Nom     : %s\n", jedi->nom);
	printf("Prenom  : %s\n", jedi->prenom);
	printf("Age     : %hu\n", jedi->age);
	printf("Taille  : %1.2f\n", jedi->taille);
	printf("Planete : %s\n", jedi->planete);
    }
}

/*
    Recherche et lit une fiche Jedi dans le fichier binaire bin
    en y accédant directement par la clé identifiant isj et affiche
    tous les champs de la fiche trouvée (appel à la fonction print_jedi).
    Retourne 1 en cas de problème, 0 sinon.

    bin : nom du fichier binaire
    isj : Identifiant Spatial Jedi recherché
*/
int16_t print_isj(char *bin, uint32_t isj)
{
    /* A compléter */

    /* Le descripteur de fichier qui fera référence au fichier binaire lu. */
    FILE *file_bin;

    /* La structure jedi pour stocker les informations du jedi recherché. */
    struct jedi jedi;

    /* On remplit la structure jedi de zéros. */
    memset(&jedi, 0, sizeof(struct jedi));

    /*
	Ensuite, on ouvre le fichier binaire en lecture.
	Notez le paramètre qui détermine le mode d'accès,
	fixé à "rb" pour "read" et "binary". Ce qui signifie...
	Bon ok vous avez compris.
    */
    file_bin = fopen(bin, "rb");
    if (file_bin == NULL) {
	/*
	    Il y a eu une erreur lors de l'ouverture du fichier.
	    Quand c'est le cas, la libc positionne une variable
	    interne qui contient le code d'erreur. La fonction
	    perror() permet d'afficher un message explicite
	    sur la sortie standard, en fonction du type d'erreur
	    rencontré.
	*/
	perror(bin);
	return EXIT_FAILURE;
    }

    /*
	La fonction fseek permet de déplacer la tête de lecture
	d'un fichier à un offset donné. L'offset est calculé
	à partir de l'isj et de la taille mémoire occupée par
	une structure jedi. Le 3e paramètre de la fonction fseek()
	permet de définir à partir d'où on effectue le déplacement.
	SEEK_SET indique qu'on se déplace à partir de début du fichier.
    */
    fseek(file_bin, isj * sizeof(struct jedi), SEEK_SET);

    /*
	La fonction fread() lit un certain nombre d'octets depuis
	le fichier, à partir de la position courante de la tête
	de lecture (déplacée par l'appel à fseek() ligne 116).
	Le premier paramètre est un paramètre de sortie : on passe
	l'adresse d'une structure jedi dont le contenu sera écrasé
	par les données lues depuis le fichier.
    */
    size_t bytes_read = fread(&jedi, sizeof(struct jedi), 1, file_bin);

    /*
	La fonction fread retourne le nombre d'octets effectivement lus
	depuis le fichier. Si ce nombre est nul, cela signifie que le déplacement
	effectué par fseek() a atteint la fin du fichier, et donc que
	le jedi recherché ne fait pas partie de la base de données.
    */
    if (bytes_read == 0) {
	printf("Fiche Jedi n° %u non trouvée\n", isj);
	fclose(file_bin);
	return EXIT_FAILURE;
    }

    /* On affiche les informations du jedi trouvé. */
    print_jedi(&jedi);

    fclose(file_bin);
    return EXIT_SUCCESS;
}

/*
    Lit dans le fichier texte (in) toutes les fiches Jedi et les écrit
    dans un fichier binaire. L'identifiant isj fera office de clé d'accès
    direct dans le fichier binaire de sortie (out)
    Retourne 1 en cas de problème, 0 sinon.

    in  : nom du fichier entrée texte (ex : r2.txt)
    out : nom du fichier sortie binaire (ex : d2.bin)

    NOTA BENE :

    Lecture texte :
    On utilisera une variable intermédiaire de type struct jedi
    pour stocker les valeurs lues dans le fichier d'entrée.
    La lecture caractère par caractère ne sera pas utilisée.
    La lecture des fiches du fichier d'entrée texte doit s'effectuer
    obligatoirement en utilisant les fonctions parmi : fgets, sscanf, fscanf
    Solution 1 : fgets + sscanf. Solution 2 : fscanf
    Coder les 2 solutions
    Quand les 2 solutions marcheront bien, amusez vous à supprimer le code isj d'une
    des lignes du fichier r2.txt
    Puis réessayez solution 1 et solution 2. Que constatez vous ?


    Ecriture binaire : on écrira directement la variable de type struct jedi à
    l'emplacement jedi.isj du fichier binaire
*/
int16_t convert_to_bin(char *in, char *out)
{
    struct jedi jedi;
    /* A compléter */
    char tampon[10*SIZE];   // On définit une taille de tampon de lecture suffisament grand
    /* Sécurisation : mise à 0 de jedi. Mettez en commentaires cette instruction et passez valgrind sur le programme, que constatez vous ? */
    memset(&jedi, 0, sizeof(struct jedi));

    /* Ouverture des fichiers entrée et sortie */
    FILE *file_in, *file_out;
    file_in = fopen(in, "rt");      // Ouverture en mode lecture, texte
    if (file_in == NULL) {
	char error_msg[300];
	sprintf(error_msg, "Fichier %s non trouvé", in);
	perror(error_msg);
	return EXIT_FAILURE;
    }
    file_out = fopen(out, "wb");    // Ouverture en mode écriture, binaire
    if (file_out == NULL) {
	char error_msg[300];
	sprintf(error_msg, "Fichier %s impossible à créer", out);
	perror(error_msg);
	fclose(file_in);
	return EXIT_FAILURE;
    }

#ifndef SOL2    // Cf. Makefile option -DSOL2 non activée
    /* Solution 1 : fgets + sscanf ; préférez cette solution "sécurisée"
    En cas de ligne défectueuse dans le fichier d'entrée, le problème restera circonscrit
    à cette ligne */
    while (fgets(tampon, 10*SIZE, file_in) != NULL) {
	sscanf(tampon, "%u %s %s %hu %f %s", &jedi.isj, jedi.nom, jedi.prenom, &jedi.age, &jedi.taille, jedi.planete);
	fseek(file_out, jedi.isj * sizeof(struct jedi), SEEK_SET);
	fwrite(&jedi, sizeof(struct jedi), 1, file_out);
    }
#else           // Cf. Makefile option -DSOL2 activée
    /* Solution 2 : fscanf ; Solution non sécurisée à éviter
    fscanf peut aller chercher une valeur sur la ligne suivante
    s'il ne l'a pas trouvée dans la ligne en cours.
    En cas de ligne défectueuse dans le fichier d'entrée, cela créera des problèmes
    sur toutes les lectures de fiches suivantes.
    Amusez vous à supprimer le code isj d'une des lignes du fichier r2.txt
    Puis réessayez solution 1 et solution 2. Que constatez vous ?*/
    while (!feof(file_in)) {
	fscanf(file_in, "%u %s %s %hu %f %s", &jedi.isj, jedi.nom, jedi.prenom, &jedi.age, &jedi.taille, jedi.planete);
	fseek(file_out, jedi.isj * sizeof(struct jedi), SEEK_SET);
	fwrite(&jedi, sizeof(struct jedi), 1, file_out);
    }
#endif
    fclose(file_in);
    fclose(file_out);
    return EXIT_SUCCESS;
}

/*
    main : à écrire complètement
    3 paramètres sont passés au programme (cf. argc, argv):
    - nom fichier texte entree
    - nom fichier binaire sortie
    - identifiant isj recherché
    Exemple d'utilisation :
    ./jedi r2.txt d2.bin 1977
    main effectue les traitements suivants :
    - vérifier que les 3 paramètres attendus sont bien présents, les récupérer
    - appeler convert_to_bin avec les paramètres adéquates
    - appeler print_isj avec les paramètres adéquates
*/
int main(int argc, char **argv)
{
    if(argc < 4) {
	printf("Paramètres attendus :\n");
	printf("- nom du fichier d'entrée texte\n");
	printf("- nom du fichier de sortie binaire\n");
	printf("- numéro Identifiant Spatial Jedi à rechercher dans le fichier binaire créé\n");
	printf("Exemple : ./jedi r2.txt d2.bin 1977\n");
	return EXIT_FAILURE;
    }
    printf("Conversion du fichier texte %s lancée\n", argv[1]);
    if (convert_to_bin(argv[1], argv[2]) != EXIT_FAILURE) {
	printf("Conversion dans le fichier binaire %s terminée\n", argv[2]);
	printf("Recherche du Jedi ayant comme Identifiant Spatial Jedi : %s\n", argv[3]);
	print_isj(argv[2], atoi(argv[3]));
    } else {
	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

```


</details>
