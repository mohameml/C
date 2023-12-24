#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ldc.h"

// Insère la valeur n en fin de la liste pointée par pl
void ldc_insere_fin(struct ldc **pl, uint32_t n)
{
    if (*pl == NULL)
    {
        // Dans ce cas la ldc est vide
        *pl = malloc(sizeof(struct ldc));
        (*pl)->numero = n;
        (*pl)->suiv = NULL;
        (*pl)->prev = NULL;
    }
    else
    {
        // si non la ldc est non vide :

        struct ldc *pointeur = *pl;
        while (pointeur->suiv != NULL)
        {
            pointeur = pointeur->suiv;
        }

        // mnt on'a un ptr vers derneiure cellule :
        pointeur->suiv = malloc(sizeof(struct ldc));
        pointeur->suiv->numero = n;
        pointeur->suiv->prev = pointeur;
        pointeur->suiv->suiv = *pl;
    }
}

// Affiche le contenu de la liste l
void ldc_affiche(struct ldc *l)
{
    if (l == NULL)
    {
        printf("votre ldc est vide \n");
    }
    else
    {
        while (l->suiv != NULL)
        {
            printf("%d ->", l->numero);
            l = l->suiv;
        }

        printf("\n");
    }
}

// Retourne le nombre d'éléments contenus dans liste l
uint32_t ldc_taille(struct ldc *l)
{
    if (l == NULL)
    {
        // votre ldc est vide donc count = 0 ;
        return 0;
    }
    else
    {
        int count = 1;

        while (l->suiv != NULL)
        {
            count++;
            l = l->suiv;
        }
    }
}

// Retourne l'élément placé n positions après e
// préconditions:
//   - e non NULL
//   - il y a au moins n éléments après e
struct ldc *ldc_recupere_nieme(struct ldc *e, uint8_t n)
{
    // en cas de précondition non rescpecte on return strcut ldc vide :

    if (e == NULL || ldc_taille(e) < n)
    {

        exit(1);
        return e;
    }
    else
    {
        // si les préconditions sont verifiées :

        int count = 0;

        while (count < n)
        {
            e = e->suiv;
            count++;
        }

        return e;
    }
}

// Supprime l'élément e de la liste pointée par pl
// et libère la mémoire associée à e.
// préconditions:
//   - *pl non vide
//   - e non NULL
//   - e dans *pl
void ldc_supprime(struct ldc **pl, struct ldc *e)
{
    if (*pl == NULL || e == NULL)
    {
        exit(1);
    }
    else
    {
        // on a verifier deux préconditions :

        struct ldc *ptr = *pl;

        while (ptr != NULL && ptr != e)
        {
            ptr = ptr->suiv;
        }

        struct ldc *style = ptr;

        // on met a jour le pointeur
        ptr->prev->suiv = ptr->suiv;
        ptr->suiv->prev = ptr->prev;

        free(style);
    }
}

// Libère la mémoire occupée par chacun des éléments
// de la liste l.
void ldc_libere(struct ldc *l)
{
    if (l == NULL)
    {
        printf("votre ldc est vide : rien a supprimer");
    }
    else
    {
        while (l != NULL)
        {
                }
    }
}