#ifndef BLOC_8_fois_8
#define  BLOC_8_fois_8


#include "tab_chaine.h"
#include "matrice.h"


/*-------------- strcut bloc 8 fois 8 : -----------------*/

typedef struct bloc_8_fois_8
{
    int position_x ;
    int position_y ;
    int data_mat[8][8];
    int data_vect_64[64];


}bloc_8_fois_8;

extern void afficher_data_vect_bloc_8_fois_8(bloc_8_fois_8 bloc );
extern void afficher_data_mat_bloc_8_fois_8(bloc_8_fois_8 bloc );



/*------------ struct MCU_BLOC :-------------------*/

typedef struct MCU_BLOC
{
    
    bloc_8_fois_8 bloc;
    struct MCU_BLOC* suiv;

}MCU_BLOC;


extern void inserer_mcu(MCU_BLOC** pl, bloc_8_fois_8 bloc);
extern void supprimer_dernier_mcu(MCU_BLOC** pl);
extern void liberer_mcu(MCU_BLOC** pl);
extern  void afficher_MCU(MCU_BLOC* pl);






/*-------- structure mcu_vect -------------*/

typedef struct mcu_vect
{
    MCU_BLOC *data_vect_Y;
    MCU_BLOC *data_vect_Cb;
    MCU_BLOC *data_vect_Cr;

} mcu_vect;


/*-------------  struct mcu_mat   --------------*/

typedef struct mcu_mat
{
    matrice data_Y;
    matrice data_Cb;
    matrice data_Cr;
}
mcu_mat;


/*-------------- structure liste_chaine_mcu : pour stocker tout le mcu dans une liste_chaine ------------ */

typedef struct liste_chaine_mcu
{
    mcu_mat data;
    struct liste_chaine_mcu  *suiv;
} liste_chaine_mcu;

void inserer_liste_chaine_mcu(liste_chaine_mcu** pl, mcu_mat mcu);
void supprimer_dernier_liste_chaine_mcu(liste_chaine_mcu** pl);
void liberer_liste_chaine_mcu(liste_chaine_mcu** pl);
void afficher_liste_chaine_mcu(liste_chaine_mcu* pl);



#endif 