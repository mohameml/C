#include <stdio.h>
#include <stdint.h>
#include "../include/YCbCr_vers_RGB.h"
#include "../include/bloc_8_fois_8.h"


void YCbCr_RGB(mcu_mat mcu)
{
    int mat_R[(const int )mcu.data_Y.taille_ligne][(const int )mcu.data_Y.taille_colone];
    int mat_G[(const int )mcu.data_Cb.taille_ligne][(const int )mcu.data_Cb.taille_colone];
    int mat_B[(const int )mcu.data_Cr.taille_ligne][(const int )mcu.data_Cr.taille_colone];


        
    
    for(int i=0; i<mcu.data_Y.taille_ligne; i++)
    {
        for(int j=0; j<mcu.data_Y.taille_colone;j++)
        {
            mat_R[i][j]=(int)(mcu.data_Y.pointeur[i][j]+1.402*(mcu.data_Cr.pointeur[i][j]-128));

            mat_G[i][j]=(int)(mcu.data_Y.pointeur[i][j]- 0.34414*(mcu.data_Cb.pointeur[i][j]-128)-0.71414*(mcu.data_Cr.pointeur[i][j]-128));

            
            mat_B[i][j]=(int)(mcu.data_Y.pointeur[i][j]+1.772*(mcu.data_Cb.pointeur[i][j]-128));

          // pour assurer que les valeures de mat R , G et B dans [0,255].

            if (mat_R[i][j] < 0) mat_R[i][j] = 0;
            if (mat_R[i][j] > 255) mat_R[i][j] = 255;

            if (mat_G[i][j] < 0) mat_G[i][j] = 0;
            if (mat_G[i][j] > 255) mat_G[i][j] = 255;

            if (mat_B[i][j] < 0) mat_B[i][j] = 0;
            if (mat_B[i][j] > 255) mat_B[i][j] = 255;
            
        }
        
    }

    for(int i =0 ; i<mcu.data_Y.taille_ligne; i++)
    {
        for(int j=0; j<mcu.data_Y.taille_colone;j++)
        {
            mcu.data_Y.pointeur[i][j] = mat_R[i][j];
            mcu.data_Cb.pointeur[i][j] = mat_G[i][j];
            mcu.data_Cr.pointeur[i][j] = mat_B[i][j];
        }

    }
    
}