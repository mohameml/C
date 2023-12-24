#include <stdio.h>
#include <stdlib.h>

void affichage(int p[] , int taille );

int main(void)
{
    int nombres_joueurs=0;
    int *listes_joueures = NULL;

    int *autre_listes=NULL;

    printf("Quel est le nombres de joueures que vous voulez: ");
    scanf("%d",&nombres_joueurs);


    listes_joueures=malloc(nombres_joueurs*sizeof(int));
    int i;
    if(listes_joueures==NULL)
    {
        exit(1);
    }
    for(i=0;i<nombres_joueurs;i++)
    {
        listes_joueures[i]=i+1;
    }

    affichage(listes_joueures,nombres_joueurs);
    

    // definition d'une autre Listes 

    

    autre_listes=calloc(nombres_joueurs,sizeof(int));
    affichage(autre_listes,nombres_joueurs);



    free(listes_joueures);
    free(autre_listes);

    
    return 0 ;
}


void affichage(int p[], int taille )
{
    printf("------------------------------------\n");
    int i ;
    for(i=0; i<taille ;i++)
    {
        printf("[%d]\n", p[i]);

    }
    printf("\n");

}
