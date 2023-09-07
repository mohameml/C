#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "../include/zig_zag_inverse.h"
#include "../include/quantification_inverse.h"
#include "../include/tab_chaine.h"
#include "../include/decodage_Huffman.h"
#include "../include/idct.h"
#include "../include/bloc_8_fois_8.h"
#include "../include/matrice.h"



/*--------------------------------- Les operations pour : bloc_8_fois_8 ---------------------*/



void afficher_data_vect_bloc_8_fois_8(bloc_8_fois_8 bloc )
{
    /*pour afficher data_vect_64de strcut bloc_8_fois_8 */

    printf("------ Bloc------ : \n");
    printf("x=%d,y=%d \n",bloc.position_x,bloc.position_y);
    printf("DATA_vect: \n");

    for(int i=0 ; i <64 ; i++)
    {

        printf("l'element d'indice %d est : %d ",i,bloc.data_vect_64[i]);
        
        printf("\n");

    }


}



void afficher_data_mat_bloc_8_fois_8(bloc_8_fois_8 bloc )
{
    /* pour afficher le data_mat de strcut de bloc_8_fois_8 */

    printf("Bloc : \n");
    printf("x=%d,y=%d \n",bloc.position_x,bloc.position_y);
    printf("DATA_mat: \n");

    for(int i=0 ; i <8 ; i++)
    {

        for(int j=0 ; j<8 ; j++)
        {
            printf("%d ",bloc.data_mat[i][j]);
        }

        printf("\n");

    }


}




/*-------------------------- Les opérations pour : MCU_BLOC -------------------------------*/

void inserer_mcu(MCU_BLOC** pl, bloc_8_fois_8 bloc)
{

    if(*pl==NULL)
    {
        /*on verifier si *pl==NULL */
        *pl = malloc(sizeof(MCU_BLOC));
        (*pl)->suiv = NULL ;
        (*pl)->bloc = bloc ;
    }
    else{
        /* On parcourt la liste jusqu'à la dernière cellule */
       MCU_BLOC* queue = *pl;

        while (queue->suiv != NULL)
        {
            queue = queue->suiv;
        }

    /* Allocation et insertion de la cellule */
        queue->suiv = malloc(sizeof(MCU_BLOC));
        assert(queue->suiv != NULL);
        queue->suiv->bloc = bloc;
        queue->suiv->suiv = NULL;

    }
    
}




void supprimer_dernier_mcu(MCU_BLOC** pl)
{
    /* cette fonction sert a supprimer le derniere bloc de la liste chaine */
    

    MCU_BLOC* prec = *pl ;   
    MCU_BLOC* p = *pl;

    while (p->suiv != NULL ) 
    {
        prec = p;
        p = p->suiv;
    }

    free(p);
    prec->suiv =NULL;
    
    
}

void liberer_mcu(MCU_BLOC** pl)
{
    /*pour liberere la liste chainee */
    while((*pl)->suiv != NULL)
    {
        supprimer_dernier_mcu( pl);
    }
    free(*pl);
    *pl=NULL;
    
}


void afficher_MCU(MCU_BLOC* pl)
{
    /*pour afficher la liste chainee */
    if (pl==NULL)
    {
        printf("votre mcu est vide\n");
    }
    else{
        while(pl->suiv!=NULL)
        {
            afficher_data_mat_bloc_8_fois_8(pl->bloc);
            pl=pl->suiv;
        }

        afficher_data_mat_bloc_8_fois_8(pl->bloc);

    }
}




/*---------------------------- Les opérations pour :liste_chaine_mcu --------------------------*/


void inserer_liste_chaine_mcu(liste_chaine_mcu** pl, mcu_mat mcu)
{
    /* cette fonction sert a inserer un mcu dans une liste chainee */

    if(*pl==NULL)
    {
        *pl = malloc(sizeof(liste_chaine_mcu));
        (*pl)->suiv = NULL ;
        (*pl)->data = mcu ;
    }
    else 
    {
        liste_chaine_mcu* queue = *pl;

        /* On parcourt la liste jusqu'à la dernière cellule */
        while (queue->suiv != NULL)
        {
            queue = queue->suiv;
        }
        /* Allocation et insertion de la cellule */
        queue->suiv = malloc(sizeof(liste_chaine_mcu));
        assert(queue->suiv != NULL);
        queue->suiv->data = mcu;
        queue->suiv->suiv = NULL;

    }




    
}

void supprimer_dernier_liste_chaine_mcu(liste_chaine_mcu** pl)
{
    /*pour supprimer le derniere mcu de la liste chainee */


    liste_chaine_mcu* prec = *pl ;   
    liste_chaine_mcu* p = *pl;

    while (p->suiv != NULL ) 
    {
        prec = p;
        p = p->suiv;
    }


    liberer_matrice(&p->data.data_Y);
    liberer_matrice(&p->data.data_Cb);
    liberer_matrice(&p->data.data_Cr);

    free(p);

    prec->suiv =NULL;

    
    
}

void liberer_liste_chaine_mcu(liste_chaine_mcu** pl)
{
    /*pour liberer la memoire */
    while((*pl)->suiv != NULL)
    {
        supprimer_dernier_liste_chaine_mcu( pl);
    }

    liberer_matrice(&(*pl)->data.data_Y);
    liberer_matrice(&(*pl)->data.data_Cb);
    liberer_matrice(&(*pl)->data.data_Cr);
    
    free(*pl);
    *pl = NULL ;
    
}


void afficher_liste_chaine_mcu(liste_chaine_mcu* pl)
{
    /*pour afficher la liste chainne si besoin oiur gdb :*/
    
    if (pl==NULL)
    {
        printf("votre mcu est vide\n");
    }
    else
    {
        while(pl!=NULL)
        {
            afficher_matrice(pl->data.data_Y);
            afficher_matrice(pl->data.data_Cb);
            afficher_matrice(pl->data.data_Cr);
            pl=pl->suiv;
        }



    }
}






