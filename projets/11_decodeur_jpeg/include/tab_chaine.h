#ifndef TAB_CHAINE
#define TAB_CHAINE
#include <stdio.h>
#include <stdint.h>
#include "matrice.h"

/*ceci est un module : tableaux des chaines qui s'appelle : tab_chaine */

typedef struct tab_chaine 
{
    int taille ; /* represente la taille de tab */
    char** pointeur ; /* represente le pointeur vers le premier case  de la tableaux  */

}tab_chaine;

extern void  ajouter_chaine(tab_chaine* p,char* chaine);
extern void liberer_tab_chaine(tab_chaine* p);
extern void afficher_tab_chaine(tab_chaine tab);



#endif 