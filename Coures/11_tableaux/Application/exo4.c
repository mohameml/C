#include <stdio.h>
void inverser(int tab[],int taille );
void affchiage(int tab[], int taille);
/*

Inverser un tableau
Produisez une fonction qui inverse le contenu d’un tableau:
   (le premier élément devient le dernier, l’avant-dernier le deuxième et ainsi de suite).
*/

int main(void)
{
    int tab[4]={1,2,3,4};


    //L'affchiage avant inverser(tab)

    printf("L'affchiage avant inverser(tab)\n");
    affchiage(tab,4);

     printf("------------------\n");
    //l'affchiage apres inverser : 
    printf("L'affchiage apres inverser(tab) \n");

    inverser(tab,4);
    affchiage(tab,4);

 
    return 0 ;
}


void inverser(int tab[],int taille )
{

    int i ;
    int parcour = (int )(taille-1)/2;
    for(i=0; i < parcour;i++)
    {
        int tmp=0;
       tmp=tab[i];
       tab[i]=tab[taille-1-i];
       tab[taille-1-i]=tmp;


    }
}


void affchiage(int tab[], int taille)
{
    int i ;

    for(i=0; i<taille ; i++)
    { 
        printf("[%d]",tab[i]);
    
    }
    printf("\n");
}