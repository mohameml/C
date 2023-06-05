#include <stdio.h>
int recherche(int tab[], int taille , int elem);
/*

Recherche d’un élément
Construisez une fonction qui teste la présence d’une valeur dans un tableau de int. 
Celle-ci retournera 1 si un ou plusieurs éléments du tableau sont égaux à la valeur recherchée, 0 sinon.

*/

int main(void)
{
    int tab[5]={1,2,3,4,5};

    int elem1 = 1;
    int elem2 = 6 ;


    printf("L'elme %d est dans tab : présence = %d\n",elem1,recherche(tab,5,elem1));
    printf("L'elme %d n'est pas dans tab : présence = %d\n",elem2,recherche(tab,5,elem2));
    
    return 0 ;
    
}


int recherche(int tab[], int taille , int elem)
{

    int n =0 ; 
    int i ;
    for(i=0; i<taille ; i++)
    {
        if (elem == tab[i])
           n=1 ;
           return n ;
    }

    return n ;
}