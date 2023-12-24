#include "../include/quantification_inverse.h"
#include "../include/tab_chaine.h"
#include "../include/decodage_Huffman.h"

void quantification_inverse(int tab[64], tab_chaine tab_quantification)
{
    // on convertit le tab_chaine vers des int 

    int tab_quantifiaction_int[64];
    for(int i=0 ; i<64 ; i++)
    {
        tab_quantifiaction_int[i]= convert_octet_to_uint8_t(tab_quantification.pointeur[i]);
    }

    // On effectue mnt la quantification inverse : 

    for(int j=0 ; j<64 ; j++)
    {
        tab[j]=tab[j]*tab_quantifiaction_int[j];
    }
}