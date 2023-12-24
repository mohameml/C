#include <stdio.h>
void  afficher(int tab[], int taille);
int *creer_tab(void);

int main(void)
{
    int *tab = creer_tab();
    
    afficher(tab,  3);

        


   return 0 ;   
}


int *creer_tab(void)
{
    static int tab[5];

    int i;
    for(i=0 ; i<5 ; i++  )
       tab[i]=1;
    
    return tab;
}

void afficher(int tab[], int taille)
{ 
    int i ;

    for (i=0; i<taille ; i++)
         printf("[%d]",tab[i]);
        
    printf("\n");


}