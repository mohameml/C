#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fonctions.h"

/* Prototypes fonctions internes au module */
static uint8_t max_char(uint8_t  char1, uint8_t  char2);
static uint8_t max_tab_char (uint8_t * son, uint32_t taille);
static uint8_t* sur_echantillonnage (uint8_t* son, uint32_t taille, uint32_t T);
static void mixage_meme_frequence(struct audio **resultat, struct audio *audio1, struct audio *audio2);

/* Retourne le maximum de 2 char/uint8_t */
static uint8_t max_char(uint8_t  char1, uint8_t  char2)
{
    /* A compléter */
}

/* Retourne le maximum d'un tableau de char/uint8_t */
static uint8_t max_tab_char (uint8_t * son, uint32_t taille)
{
    /* A compléter */
}

/* Sur echantillonne son dans un rapport de T. Retourne un pointeur sur le resultat */
static uint8_t* sur_echantillonnage (uint8_t* son, uint32_t taille, uint32_t T)
{
    /* A compléter */
}

/* Mixage de 2 sons de meme frequence */
static void mixage_meme_frequence(struct audio **resultat, struct audio *audio1, struct audio *audio2)
{
    /* A compléter */
    /* Pour le champ name du nouveau son résultat :
       - Version de base : mettre "mix" en écrivant caractère par caractère dans le champ name
       - Version avancée uniquement pour ceux qui le souhaitent : utiliser les fonctions de traitement de chaines
	 de caractères pour que le nom agrège les noms des 2 sons mixés */
}

/*  Mixage de 2 sons de frequences proportionnelles :
    Sur echantillonne le son de frequence plus petite
    pour le mettre a la meme frequence que l'autre son.
    Appelle la fonction de mixage de 2 sons de même fréquence */
void mixage(struct audio **resultat, struct audio *audio1, struct audio *audio2)
{
    /* A compléter */
}
