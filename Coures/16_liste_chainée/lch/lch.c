#include <stdio.h>
#include "lch.h"

/*
------------------- fonctions des Affichages : --------------------
*/

void AfficheListe(liste *tete)
{
    // affiche le contenu d'une liste chaineé

    if (tete == NULL)
    {
        printf("votre liste chaineé est vide : rien à afficher \n");
    }
    else
    {
        while (tete->suiv != NULL)
        {
            printf("%d ->", tete->val);
        }
        printf("%d -> NULL \n", tete->val);
    }
}

void AfficherlisteRec(liste *tete)
{
    // affiche le contenu d'une liste chainée  d'une Maniére Reccursive

    if (tete == NULL)
    {
        printf("votre liste chaineé est vide : rien à afficher");
    }
    else
    {
        if (tete->suiv == NULL)
        {
            printf("%d -> \n", tete->val);
        }
        else
        {
            printf("%d ->", tete->val);
            AfficherlisteRec(tete->suiv);
        }
    }
}

void AfficherListeRecInverse(liste *tete)
{
    // afficher le contenu d'une liste chainée inverser d'une Maniére Reccursive
}