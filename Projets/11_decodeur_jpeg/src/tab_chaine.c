#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "../include/tab_chaine.h"


/*---------fonction: ajouter_chaine : ----------------*/

void  ajouter_chaine(tab_chaine* p,char* chaine)
{
    if(p->pointeur==NULL)
    {
        /* le tab est initialement vide */
        
        /* alloction pour la pointeur de data */
        p->pointeur=malloc(sizeof(char*));
        assert(p->pointeur!=NULL);
         
        /* allocation pour le pointeur de chaine de caractere */
        *(p->pointeur)=malloc(sizeof(char)*(strlen(chaine)+1));
        assert((p->pointeur)!=NULL);
        
        strcpy(*(p->pointeur),chaine);

        /* on initialise  la taille de la tab_chaine */
        p->taille = 1;
        
        


    }
    else
    {
        /* si le tab n'est pas vide */
        
        int taille= p->taille;

        /*on fait une realloc de data */
        p->pointeur = realloc(p->pointeur,(taille+1)*sizeof(char*));
        assert(p->pointeur!=NULL);
        p->pointeur[taille]=malloc(sizeof(char)*(strlen(chaine)+1));
        assert(p->pointeur[taille]);
        strcpy(p->pointeur[taille],chaine);
        /* on increment  la taille de la tab_chaine */
        p->taille++;
        


    }
}

/*------------------------fonction : liberer_tab_chaine--------------------------*/


void liberer_tab_chaine(tab_chaine* p)
{
    /*pour libere la memoire */
    if(p==NULL)
    {
        printf("votre tab est vide \n");
    }
    else
    {
        int taille = p->taille;
        for(int i=0;i <taille;i++)
        {
            free(p->pointeur[i]);
        }
        free(p->pointeur);
        

    }

}

/*--------------------fonction :afficher_tab_chaine ------------------------------------------- */


void afficher_tab_chaine(tab_chaine tab)
{
    /* l'affichage d'une tab_chiane */
    if(tab.pointeur==NULL)
    {
        printf("votre tab_chaine est vide : rien a aficher\n");
    }
    else
    {
        int taille = tab.taille;
        for(int i=0;i<taille;i++)
        {
            printf("l'elemnt d'indice %d de votre tab_chaine est : %s\n",i,tab.pointeur[i]);
        }

    }

}





















