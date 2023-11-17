# Enoncé

Dans cet exercice, vous allez devoir allouer et initialiser des
structures de données complexes. Les fonctions qui effectuent
l'allocation de ces structures de données seront de deux formes
différentes. Dans un premier cas, la fonction renvoie un pointeur vers
la structure de données allouée et initialisée. Dans un autre cas, la
structure de données à allouer est passée en paramètre de la fonction,
et la fonction ne renvoie rien (procédure).

De manière symétrique, on étudiera la libération de ces structures de
données, avec modification ou non du pointeur passé en paramètre de la
fonction de libération.

Une fonction main permettant de tester votre programme est
fournie. Bien entendu, en plus de l'affichage des deux contacts sur la
sortie standard, votre programme ne devra pas comporter de fuite
mémoire (demandez à `valgrind` de vous en donner la preuve).

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/contact/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

`struct contact **nouveau_contact` vous donne la nausée? Pas de
  panique. Commencez par regarder comment la fonction `creer_contact`
  est appelée par le `main`. Ensuite, rappelez vous que `type
  *nom_variable` déclare simplement un pointeur sur une donnée de type
  `type`. Si on applique cette définition, `struct contact
  **nouveau_contact` est simplement un pointeur qui pointe sur un
  pointeur (de `struct contact`)!

Pourquoi vous infliger ce `**` alors? Tout simplement parce que vous
allez devoir modifier un paramètre de fonction.  Si ça ne vous parle
toujours pas, courez (re)lire la fiche **Passage de paramètre par
copie** du kit de démarrage (section Pointeurs).

</details>

# Compétences

* Fonctions de copies de chaines de caractères
* Fonctions de longueur d'une chaine de caractères
* Passage en paramètre de pointeurs de pointeurs
* Allocation de mémoire dynamique type de donnée complexe
* Libération de mémoire
* Pointeurs de pointeurs
* Gestion d'erreurs à base de perror

# Difficulté

:star: :star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: contact

.PHONY: clean
clean:
	rm -f *~ *.o contact

```

#### Corrigé du fichier contact.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/* Structure de données représentant l'adresse postale d'un
   contact. */
struct adresse
{
    uint16_t numero;
    char *rue;
    uint32_t code_postal;
    char *pays;
};

/* Structure de données représentant un contact. */
struct contact
{
    char *prenom;
    char *nom;
    struct adresse *adr;
};

/*
   Petite fonction inline pour factoriser la vérification de l'adresse
   retournée par calloc. Si calloc échoue, le programme s'arrête.
   */
static inline void *verified_calloc(size_t count, size_t size)
{
    void *ret = calloc(count, size);
    if (ret == NULL) {
	perror("An error occurred while allocating from annuaire.c.");
	exit(EXIT_FAILURE);
    }
    return ret;
}

/*
   Fonction de création d'une adresse postale. Elle retourne une
   adresse postale nouvellement allouée et initialisée en fonction des
   paramètres numero, rue, code_postal et pays.
   */
static struct adresse *creer_adresse(uint16_t numero,
				     const char *rue,
				     uint16_t code_postal,
				     const char *pays)
{
    struct adresse *adr = NULL;
    adr = verified_calloc(1, sizeof(struct adresse));
    size_t taille_rue = strlen(rue) + 1;
    size_t taille_pays = strlen(pays) + 1;
    adr->rue = verified_calloc(taille_rue, sizeof(char));
    adr->pays = verified_calloc(taille_pays, sizeof(char));

    adr->numero = numero;
    strncpy(adr->rue, rue, taille_rue);
    adr->code_postal = code_postal;
    strncpy(adr->pays, pays, taille_pays);
    return adr;
}

/*
   Fonction de création d'un contact. A la différence de
   creer_adresse, on ne va pas retourner le contact nouvellement
   alloué et initialisé, mais on va plutôt allouer et initialiser le
   (struct contact *) dont l'adresse est passée dans le paramètre
   nouveau_contact.
   */
static void creer_contact(struct contact **nouveau_contact,
			  const char *prenom,
			  const char *nom,
			  uint16_t numero,
			  const char *rue,
			  uint16_t code_postal,
			  const char *pays)
{
    struct adresse *adr = creer_adresse(numero, rue, code_postal, pays);
    *nouveau_contact = verified_calloc(1, sizeof(struct contact));
    struct contact *c = *nouveau_contact;
    size_t taille_prenom = strlen(prenom) + 1;
    size_t taille_nom = strlen(nom) + 1;
    c->prenom = verified_calloc(taille_prenom, sizeof(char));
    c->nom = verified_calloc(taille_nom, sizeof(char));
    strncpy(c->prenom, prenom, taille_prenom);
    strncpy(c->nom, nom, taille_nom);
    c->adr = adr;
}

/*
   Libère l'adresse postale passée en paramètre. En sortie, le pointeur
   qui pointait sur cette adresse vaut NULL.
   */
static void liberer_adresse(struct adresse **adr)
{
    free((*adr)->rue);
    free((*adr)->pays);
    free(*adr);
    *adr = NULL;
}

/*
   Libère le contact passé en paramètre. Notez qu'ici, on ne spécifie
   rien sur la valeur que doit prendre le pointeur qui pointait sur le
   contact libéré après exécution de la fonction liberer_contact.
   */
static void liberer_contact(struct contact *c)
{
    liberer_adresse(&c->adr);
    free(c->prenom);
    free(c->nom);
    free(c);
}

/*
   Affiche le contact passé en paramètre (son prénom, son nom, son
   adresse) sur la sortie standard.
   */
static void afficher_contact(struct contact *c)
{
    printf("First name : %s\n", c->prenom);
    printf("Last name : %s\n", c->nom);
    printf("Address : %u %s %u %s\n\n",
	    c->adr->numero,
	    c->adr->rue,
	    c->adr->code_postal,
	    c->adr->pays);
}


int main(void)
{
    struct contact *led_zep = NULL, *acdc = NULL;
    creer_contact(&led_zep, "Led", "Zeppelin", 1, "Stairway to Heaven", 1977, "UK");
    creer_contact(&acdc, "AC", "DC", 666, "Highway to Hell", 1979, "Australia/UK");

    afficher_contact(led_zep);
    afficher_contact(acdc);

    liberer_contact(led_zep);
    liberer_contact(acdc);

    return EXIT_SUCCESS;
}

```


</details>
