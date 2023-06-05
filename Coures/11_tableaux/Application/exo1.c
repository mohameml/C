#include <stdio.h>

/*
Réalisez une fonction qui calcule la somme de tous les éléments d’un tableau de int.
*/

int somme(int tab[],int taille);


int main(void)
{
   
    int tab[5]={1,2,3,4,5};

    int n=somme(tab , 5) ;

    printf("la somme des elemts de votre tableau est : %d \n",n);
    
    return 0 ;
}


int somme(int tab[],int taille)
{
    int somme = 0;
    int i ;
    for(i=0; i<taille ; i++ )
    {
        somme+=tab[i];

    }

    return somme ;

}