#ifndef MATRICE
#define MATRICE
#include <stdio.h>
#include <stdint.h>


/* MODULE : MATRICE CARRE */

typedef struct matrice 
{
    int taille_ligne ; /* represente le nombres des lignes  */
    int taille_colone ; /* represente le nombre des colones */
    uint8_t** pointeur ; /* represente le pointeur vers le premier case  de la tableaux  */

}matrice;


extern void initialiser_matrice(matrice* p , int taille_mat_ligne , int taille_mat_colone );
extern void ajouter_elem(matrice* p,uint8_t elem , int indice_i , int indice_j );
extern void ajouter_ligne (matrice* p,int* ligne ,int taille_ligne , int indice_ligne );
extern void liberer_matrice(matrice* p);
extern void afficher_matrice(matrice mat);
extern void ajouter_ligne_uint8_t (matrice* p,uint8_t* ligne ,int taille_ligne , int indice_ligne );




#endif 