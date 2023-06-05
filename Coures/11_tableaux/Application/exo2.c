#include <stdio.h>
int max(int tab[], int taille);
int min(int tab[], int taille);

/*
Maximum et minimum
Créez deux fonctions : une qui retourne le plus petit élément d’un tableau de int 
et une qui renvoie le plus grand élément d’un tableau de int.
*/



int main(void)
{
    int tab[5]={1,2,3,4,5};

    int max_tb=0 ; 
    int min_tb = 0;
    max_tb = max(tab,5);
    min_tb = min(tab,5);
    printf("le max de votre tab est : %d \n",max_tb);
    printf("Le min de votre tab est : %d \n",min_tb);
    return 0 ;
}


int max(int tab[], int taille)
{
    int max =0 ;
    int i ;
    for(i=0 ; i<taille ; i++)
    {
        if (tab[i]>max)
           max = tab[i] ;
        
        
        
    }

    return max ;
}

int min(int tab[], int taille)
{
    int min =0 ;
    int i ;
    for(i=0 ; i<taille ; i++)
    {
        if (tab[i]<min)
           min = tab[i] ;
        
        
        
    }

    return min ;
}