#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 16     // taille des tableaux profils_masques et profils_noms

/*  Definir ici 2 constantes hexadecimales : CON ayant pour valeur ff00 et PERLE ayant pour valeur 00ff
    CON représente ainsi un profil ayant tous les défauts et aucune qualité
    PERLE représente ainsi un profil ayant toutes les qualités et aucun défaut */

/*
    Affiche les qualités et défauts de l'individu ayant ce profil passé en paramètre
    Exemple d'affichage (la valeur du profil est à afficher en héxadécimal) :
    Voici les qualites et defauts de cet individu de profil (hexa) 1010 :
    Bienveillant Blessant
    Faire l'analyse simplifiée suivante du profil et afficher les messages correspondants :
    - Cas : tous les défauts et aucune qualité, afficher :
      Ouh la, attention, ce profil est celui d'un gros c... !
    - Cas : toutes les qualités et aucune défaut, afficher :
      Wouah, ce profil est celui d'une perle !
    - Cas : nombre de qualités supérieur ou égal au nombre de défauts, afficher :
      Ce profil est plutot bon.
    - Cas : nombre de qualités inférieur au nombre de défauts, afficher :
      Ce profil est plutot mauvais.
*/
/* Compléter les paramètres passés à la fontion : un profil, le tableau des masques de profil, le tableau des noms de profil */
void affiche_profil(
)
{
    /* A compléter : code de la fonction */
}

/*
    main
*/
int main(int argc, char **argv)
{
    /* Tableau des masques de profil */
    /* A compléter : initialisation des valeurs de profil_masques avec des constantes binaires */
    const uint16_t profil_masques[SIZE] = {
    };

    /* Tableau des noms des éléments de profil */
    const char *profil_noms[SIZE] = {
	"Diplomate", "Courageux", "Altruiste", "Bienveillant",
	"Empathique", "Honnete", "Loyal", "Gentil",
	"Intolerant", "Arrogant", "Abrupt", "Blessant",
	"Calculateur", "Cruel", "Hypocrite", "Indiscret"
    };

    /* Profil passé en paramètre */
    uint16_t profil;
    /* A compléter : remplir profil à partir des paramètres d'appel du programme
       et appeler affiche_profil */
    /* Fin A compléter */
    return EXIT_SUCCESS;
}
