#include <stdio.h>

void afficher(int tab[], int taille);

#define TAILLE 3

int main(void)
{
    int taille=3;
    int tab[TAILLE]={4,0,1};
    // affichage de tableau 
    
    afficher(tab,TAILLE);

    

    

    return 0 ;
}


void afficher(int tab[], int taille)
{ 
    int i ;

    for (i=0; i<taille ; i++)
         printf("[%d]",tab[i]);
        
    printf("\n");

}

