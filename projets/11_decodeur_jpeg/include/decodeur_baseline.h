#ifndef DECODEUR_BASELINE
#define DECODEUR_BASELINE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#include "../include/tab_chaine.h"
#include "../include/lecture_en_tete.h"
#include "../include/decodage_Huffman.h"
#include "../include/quantification_inverse.h"
#include "../include/zig_zag_inverse.h"
#include "../include/idct.h"
#include "../include/YCbCr_vers_RGB.h"
#include "../include/bloc_8_fois_8.h"


/*---------------------- Decodeur baseline : MODE SEQUENTIELLE -----------------*/

void decodeur_baseline(char* nom_fichier);

char* recupere_nom_ppm(char* nom_fichier , int nb_comp);

void remplissage_image_gris(FILE* fichier  ,MCU_BLOC** image, int largeur_image , int hauteur_image , char* image_en_bin ,tab_chaine decode_huffman_Y_DC , tab_chaine  decode_huffman_Y_AC ,int* DC_precedent,  int* compteur,tab_chaine tab_quantification_Y);

void traite_bloc(bloc_8_fois_8* bloc , char* image_en_bin, tab_chaine decode_huffman_Y_DC ,tab_chaine decode_huffman_Y_AC ,int* DC_precedent, int* compteur, tab_chaine tab_quant);

void traite_mcu(liste_chaine_mcu** image, mcu_vect *mcu_flux, char *image_en_bin, tab_chaine tab_Hufffman_Y_DC, tab_chaine tab_Hufffman_Y_AC, tab_chaine tab_Hufffman_Cb_Cr_DC, tab_chaine tab_Hufffman_Cb_Cr_AC, tab_chaine SOS, tab_chaine SOFO, int *compteur, int *DC_precedent_Y, int *DC_prcedent_Cb, int *DC_precednt_Cr, tab_chaine tab_quant_Y, tab_chaine tab_quant_Cb_Cr);

void remplissage_image_couleur(FILE* fichier ,liste_chaine_mcu** image, int largeur_image , int hauteur_image , char* image_en_bin ,tab_chaine decode_huffman_Y_DC , tab_chaine  decode_huffman_Y_AC , tab_chaine deocde_huffman_Cb_Cr_DC , tab_chaine deocde_huffman_Cb_Cr_AC ,     int* DC_precedant_Y , int *DC_precedant_Cb ,int* DC_precedant_Cr ,  int* compteur ,tab_chaine tab_quant_Y , tab_chaine tab_quant_Cb_Cr , tab_chaine SOFO , tab_chaine SOS );


#endif 