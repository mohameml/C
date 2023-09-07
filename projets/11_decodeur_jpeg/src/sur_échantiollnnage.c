#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/matrice.h"
#include "../include/bloc_8_fois_8.h"
#include "../include/tab_chaine.h"
#include "../include/lecture_en_tete.h"
#include "../include/decodage_Huffman.h"



void  sur_echantiollnnage(mcu_mat* ptr_mcu)
{


    /* initialiser la matrice de cb*/

    int hy = ptr_mcu->data_Y.taille_colone/8 ;

    int vy = ptr_mcu->data_Y.taille_ligne/8 ;

    int hcb = ptr_mcu->data_Cb.taille_colone/8 ;

    int vcb = ptr_mcu->data_Cb.taille_ligne/8 ;


    matrice  mat_cb_surechant;
    mat_cb_surechant.pointeur=NULL;

    initialiser_matrice(&mat_cb_surechant,vy*8,hy*8);


    /* initialiser la matrice de cr*/
    matrice  mat_cr_surechant;
    mat_cr_surechant.pointeur=NULL;

    initialiser_matrice(&mat_cr_surechant,vy*8,hy*8);


    for (int i=0; i< vy*8; i++)
    {
        if(i<hcb*8 )
        {
        for (int j=0; j< hy*8; j++)
        {
            if(j<vcb*8)
            {

                ajouter_elem(&mat_cb_surechant,ptr_mcu->data_Cb.pointeur[i][j],i,j);


                ajouter_elem(&mat_cr_surechant,ptr_mcu->data_Cr.pointeur[i][j],i,j);
            }
            else
            {

            
            ajouter_elem(&mat_cb_surechant,ptr_mcu->data_Cb.pointeur[i][j-8],i,j);

            ajouter_elem(&mat_cr_surechant,ptr_mcu->data_Cr.pointeur[i][j-8],i,j);
            }
        }
        }


        else {
            for (int j=0; j< hy*8; j++)
        {
            if(j<vcb*8)
            {

                ajouter_elem(&mat_cb_surechant,mat_cb_surechant.pointeur[i-8][j],i,j);


                ajouter_elem(&mat_cr_surechant,mat_cr_surechant.pointeur[i-8][j],i,j);
            }
            else
            {

            ajouter_elem(&mat_cb_surechant,mat_cb_surechant.pointeur[i-8][j-8],i,j);

            ajouter_elem(&mat_cr_surechant,mat_cr_surechant.pointeur[i-8][j-8],i,j);
            }
        }

        }
    }
    
    liberer_matrice(&ptr_mcu->data_Cb);
    liberer_matrice(&ptr_mcu->data_Cr);

    ptr_mcu->data_Cb = mat_cb_surechant;
    ptr_mcu->data_Cr = mat_cr_surechant;


    

}


void data_vect_vers_data_mat(mcu_vect mcu_flux, mcu_mat *mcu, tab_chaine SOFO)
{
    /*---------- Y -----------------*/

    // data_vect_Y vers data_Y de mcu_mat

    tab_chaine info_comp_Y = extracte_info_composante("Y", SOFO);
    mcu->data_Y.pointeur = NULL;
    initialiser_matrice(&mcu->data_Y, convert_nibble_to_uint8_t(info_comp_Y.pointeur[1][1]) * 8, convert_nibble_to_uint8_t(info_comp_Y.pointeur[1][0]) * 8);
    liberer_tab_chaine(&info_comp_Y);

    // On remplir la matrice de Y
    MCU_BLOC *data_Y = mcu_flux.data_vect_Y;

    int compteur_ligne = mcu->data_Y.taille_ligne / 8;
    int compteur_colone = mcu->data_Y.taille_colone / 8;



    for (int parcour_ligne = 0; parcour_ligne < compteur_ligne; parcour_ligne++)
    {
        for (int parcour_colone = 0; parcour_colone < compteur_colone; parcour_colone++)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    ajouter_elem(&mcu->data_Y, data_Y->bloc.data_mat[i][j], parcour_ligne * 8 + i, parcour_colone * 8 + j);
                }
            }
            data_Y = data_Y->suiv;
        }
    }




    /*---------- Cb -----------------*/

    // data_vect_Cb vers data_Cb de mcu_mat

    tab_chaine info_comp_Cb = extracte_info_composante("Cb", SOFO);
    mcu->data_Cb.pointeur = NULL;
    initialiser_matrice(&mcu->data_Cb, convert_nibble_to_uint8_t(info_comp_Cb.pointeur[1][1]) * 8, convert_nibble_to_uint8_t(info_comp_Cb.pointeur[1][0]) * 8);
    liberer_tab_chaine(&info_comp_Cb);

    // On remplir la matrice de Cb

    MCU_BLOC *data_Cb = mcu_flux.data_vect_Cb;

    int compteur_ligne_Cb = mcu->data_Cb.taille_ligne / 8;
    int compteur_colone_Cb = mcu->data_Cb.taille_colone / 8;

    for (int parcour_ligne = 0; parcour_ligne < compteur_ligne_Cb; parcour_ligne++)
    {
        for (int parcour_colone = 0; parcour_colone < compteur_colone_Cb ; parcour_colone++)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    ajouter_elem(&mcu->data_Cb, data_Cb->bloc.data_mat[i][j], parcour_ligne * 8 + i, parcour_colone * 8 + j);
                }
            }
            data_Cb = data_Cb->suiv;
        }
    }

    /*---------- Cr -----------------*/

    // data_vect_Cr vers data_Cr de mcu_mat
    tab_chaine info_comp_Cr = extracte_info_composante("Cr", SOFO);
    mcu->data_Cr.pointeur = NULL;
    initialiser_matrice(&mcu->data_Cr, convert_nibble_to_uint8_t(info_comp_Cr.pointeur[1][1]) * 8, convert_nibble_to_uint8_t(info_comp_Cr.pointeur[1][0]) * 8);
    liberer_tab_chaine(&info_comp_Cr);

    // On remplir la matrice de Cr

    MCU_BLOC *data_Cr = mcu_flux.data_vect_Cr;

    int compteur_ligne_Cr = mcu->data_Cr.taille_ligne / 8;
    int compteur_colone_Cr = mcu->data_Cr.taille_colone / 8;

    for (int parcour_ligne = 0; parcour_ligne < compteur_ligne_Cr ; parcour_ligne++)
    {
        for (int parcour_colone = 0; parcour_colone < compteur_colone_Cr; parcour_colone++)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    ajouter_elem(&mcu->data_Cr, data_Cr->bloc.data_mat[i][j], parcour_ligne * 8 + i, parcour_colone * 8 + j);
                }
            }
            data_Cr = data_Cr->suiv;
        }
    }


    liberer_mcu(&(mcu_flux.data_vect_Y));
    liberer_mcu(&(mcu_flux.data_vect_Cb));
    liberer_mcu(&(mcu_flux.data_vect_Cr));
}
