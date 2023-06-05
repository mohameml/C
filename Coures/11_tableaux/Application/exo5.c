#include <stdio.h>




int multp_somme_lignes(int taille_ligne , int taille_colone , int tab[taille_ligne][taille_colone] );
/*
Produit des lignes
Composez une fonction qui calcule le produit de la somme des 
éléments de chaque ligne d’un tableau de int à deux dimensions (ce tableau comprend cinq lignes et cinq colonnes).

*/

int main(void)
{
    int taille_ligne = 3 ;
    int taille_colone = 3 ;
    int tab[3][3]=
    {
        {1,1,1},
        {2,2,2},
        {3,0,0}
    };
    

    printf("le produit de la somme des  éléments de chaque ligne de votre Matrice est : %d\n",multp_somme_lignes(3,3,tab));
    return 0;

}


int multp_somme_lignes(int taille_ligne , int taille_colone , int tab[taille_ligne][taille_colone] )
{
    int i ,j ;
    
    int nombre = 1;
    for(i=0 ; i<taille_ligne ; i++ )
    {
        int s =0 ;
        for(j=0;j<taille_colone;j++)
        {
            s = s + tab[i][j];


        }
        nombre *= s;
        

    }

    return nombre ;


}