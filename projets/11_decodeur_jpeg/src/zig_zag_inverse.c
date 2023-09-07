#include <stdio.h>
#include <stdlib.h>
#include "../include/zig_zag_inverse.h"


void zig_zag_inverse(int tab[64], int mat[8][8])
{
    // initialiser  ptr a 0 pour parcourir le tableau d'entree 
    int ptr = 0;

    // le 1er element du tableau est dans la 1ere case de la matrice
    mat[0][0] = tab[0];

    // on parcourt les lignes de la matrice et si la ligne est paire on stocke 
    // les elemnet en remantant dans la colonne  jusque a la 1 ere ligne sinon 
    // dans le sens inverse
    for(int i = 0; i<8; i++)
    {
        if(i%2 ==0)
        {
            for(int k =0; k<= i; k++)
            {
                mat[i-k][k]=tab[ptr];
                ptr++;
            }
        }
        else
        {
            for(int k =0; k<= i; k++)
            {
                mat[k][i-k]=tab[ptr];
                ptr++;
            }
        }
    }

    // aprés avoir rempli la moitié superieure de la matrice on parcourt les colonnes 
    for(int i= 1; i<8;i++)
    {
        // si la colonne est impair
        if(i%2==1)
        {
            // on initialise r a 7 pour  parcourir la matrice de 7 eme ligne en ascendant (en ligne)
            int r= 7;
            for(int k=i; k<8; k++)
            {
                
                mat[r][k]=tab[ptr];
                r--;
                ptr++;

            }
        }
        else
        {

            // sinon on initialise r a 0 pour  parcourir la matrice de 7 eme colonne en descendant(en colonne)
            int l = 7;

            for(int k=i; k<8; k++)
            {
                 
                mat[k][l]=tab[ptr];
                l--;
                ptr++;
            }
        }

    }

}

