#ifndef DECODAGE_HUFFMAN
#define DECODAGE_HUFFMAN
#include <stdio.h>
#include <stdint.h>
#include "tab_chaine.h" 
#include "bloc_8_fois_8.h"
/*------------------------ MODULE : Decodage_HUFFMAN -------------------------------------- */

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE I DU MODULE :Decodage de TAB Huffman .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

int somme_bin(int a,int b);
void code_bin(int val,int taille,char* tab);
tab_chaine decodage_tab_huffman(tab_chaine tab_huffman );


/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE II DU MODULE : Transformation de L'image en binaire  .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

char* transformatin_image_en_binnaire(tab_chaine image);


/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE III DU MODULE : Decodage des coeff DC et AC  .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/


void avance_chaine(char** chaine, char elem );

int valide_magnitude(char* chaine , tab_chaine tab_huffman );

int indice_magnitude(char* chaine , tab_chaine tab_huffman);

int decode_val_exacte(char** chaine);

void bar(char** chaine);

void decodage_RLE(char* image_bin_AC,tab_chaine tab_huffman_AC, int tableau_des_val_AC[], int* indice , int* compteur);

void decodage_image_Huffman(char* image_en_bin, tab_chaine tab_huffman_DC , tab_chaine tab_huffman_AC, int image_decode[] , int* DC_precedent ,int*  compteur);

void decodage_Huffman_mcu(mcu_vect *mcu_flux, char *image_en_bin, tab_chaine tab_Huffman_Y_DC, tab_chaine tab_Huffman_Y_AC, tab_chaine tab_Huffman_Cb_Cr_DC, tab_chaine tab_Huffman_Cb_Cr_AC, tab_chaine SOS, tab_chaine SOFO, int *compteur, int *DC_precedent_Y, int *DC_precedent_Cb, int *DC_precednt_Cr);







/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE IV DU MODULE : Des fonctions supplémentaires .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
uint8_t convert_octet_to_uint8_t(char* octet);
uint16_t convert_bin_to_uint16_t(char* octet);
uint8_t convert_nibble_to_uint8_t(char lettre);
uint16_t convert_octet_to_uint16_t(char* octet);


#endif 