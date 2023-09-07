#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "../include/matrice.h"
#include "../include/bloc_8_fois_8.h"



void initialiser_matrice(matrice* p , int taille_mat_ligne , int taille_mat_colone )
{
    if(p->pointeur==NULL)
    {
        // la taille :
        p->taille_ligne = taille_mat_ligne;
        p->taille_colone = taille_mat_colone;


        // On initialise la matrice  de taille fournis en parametre par des  OO  :
        p->pointeur=malloc(sizeof(int*)*taille_mat_ligne);
        for(int i =0 ;i<taille_mat_ligne;i++)
        {
            p->pointeur[i]=malloc(sizeof(int)*taille_mat_colone);
            for(int j=0 ; j<taille_mat_colone ; j++)
            {
                p->pointeur[i][j]=0;
            }
        }

        
    }
    else
    {
        fprintf(stderr,"votre matrice est deja initialiser  \n");

    }
}


void ajouter_elem(matrice* p,uint8_t elem , int indice_i , int indice_j )
{
    if(p->pointeur==NULL)
    {
        fprintf(stderr,"Votre matrice n'est pas initialiser  : i faut l'initialiser avant d'ajouter un element \n");
    }
    else
    {
        // il faut verifier que les deux indices existent dans la matrice :
        assert(indice_i < p->taille_ligne);
        assert(indice_j < p->taille_colone);

        // 
        p->pointeur[indice_i][indice_j]=elem;

    }
}


void ajouter_ligne (matrice* p,int* ligne ,int taille_ligne , int indice_ligne )
{
    if(p->pointeur==NULL)
    {
        fprintf(stderr,"Votre matrice n'est pas initialiser  : i faut l'initialiser avant d'ajouter un element \n");
    }
    else
    {
        
        
        // On verifier la compatibilte entre  ligne et matrcice 
        assert(taille_ligne <= p->taille_colone);

        // et si tout passe bien On ajoute  la ligne  a l'indice i fourni 

        for(int j =0 ; j<taille_ligne;j++)
        {
            p->pointeur[indice_ligne][j]=ligne[j];
        }


    }



}


void afficher_matrice(matrice mat)
{
    if(mat.pointeur==NULL)
    {
        fprintf(stderr,"Votre matrice est vide : rien a afficher");
    }
    else
    {
        
        printf("---------------------VOICI_VOTRE_MATRICE:---------------------------------------\n");
        for(int i=0 ; i<mat.taille_ligne ; i++)
        {
            printf("[ ");
            for(int j=0;j<mat.taille_colone ; j++)
            {
                printf("%d ",mat.pointeur[i][j]);

            }
            printf(" ]\n");
        }
        printf("\n");
    }
}


void liberer_matrice(matrice* p)
{
    if(p->pointeur==NULL)
    {
        fprintf(stderr,"votre matrice ne contient rien : rien  a libere \n");
    }
    else
    {
        
        for(int j=0 ; j<p->taille_ligne ;j++)
        {
            free(p->pointeur[j]);
        }

        free(p->pointeur);
    }

}






