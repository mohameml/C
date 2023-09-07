#ifndef LECTURE_EN_TETE
#define LECTURE_EN_TETE
#include <stdio.h>
#include "tab_chaine.h"

/* 
                
MODULE : LECTURE_EN_TETE


*/


/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE I DU MODULE : Récuperation de l'entete_jpeg.                                                             
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

void  redriction_entete_jpeg(FILE* fichier,char* nom_fich);
void lectrue_section_SOFO(FILE* fichier, char* octet,tab_chaine* p_SOFO ,tab_chaine* p_SOS,tab_chaine* p_APP0,tab_chaine* p_DQT,tab_chaine* p_DHT,tab_chaine* p_COM);
void lectrue_section_SOS(FILE* fichier, char* octet,tab_chaine* p_SOFO ,tab_chaine* p_SOS,tab_chaine* p_APP0,tab_chaine* p_DQT,tab_chaine* p_DHT,tab_chaine* p_COM);
void lectrue_section_APPO(FILE* fichier, char* octet,tab_chaine* p_SOFO ,tab_chaine* p_SOS,tab_chaine* p_APP0,tab_chaine* p_DQT,tab_chaine* p_DHT,tab_chaine* p_COM);
void lectrue_section_DQT(FILE* fichier, char* octet,tab_chaine* p_SOFO ,tab_chaine* p_SOS,tab_chaine* p_APP0,tab_chaine* p_DQT,tab_chaine* p_DHT,tab_chaine* p_COM);
void lectrue_section_DHT(FILE* fichier, char* octet,tab_chaine* p_SOFO ,tab_chaine* p_SOS,tab_chaine* p_APP0,tab_chaine* p_DQT,tab_chaine* p_DHT,tab_chaine* p_COM);
void  lectrue_section_COM(FILE* fichier, char* octet,tab_chaine* p_SOFO ,tab_chaine* p_SOS,tab_chaine* p_APP0,tab_chaine* p_DQT,tab_chaine* p_DHT, tab_chaine* p_COM);
int valide_section(char* octet);
void extraction_sections(FILE* fichier,char* octet,tab_chaine* p_SOFO,tab_chaine* p_SOS,tab_chaine* p_APP0,tab_chaine* p_DQT,tab_chaine* p_DHT,tab_chaine* p_COM);
void octet_suivant(char* octet,FILE* fichier);



/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE II DU MODULE : Extraction de differents infos a partir de l'entete_jpeg.
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

tab_chaine taille_image(tab_chaine SOFO);
tab_chaine extraction_image(tab_chaine SOS  );
tab_chaine extracte_info_composante(char* composant , tab_chaine SOFO);
char*  extracte_indice_huffman(char* composante , tab_chaine SOS , tab_chaine SOFO);
int nombres_composantes(tab_chaine SOFO);
tab_chaine extracte_tab_huffamn(char* composante , char* type , tab_chaine DHT , tab_chaine SOS , tab_chaine SOFO);
tab_chaine  exctracte_table_quantification(char* composante , tab_chaine DQT , tab_chaine SOFO);
tab_chaine order_appartion_comp(tab_chaine SOFO, tab_chaine SOS);
int nb_appration_bloc_8_fois_8_dans_mcu(char *composante, tab_chaine SOFO);



/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE III DU MODULE : Des fonctions supplémentaires .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

char* concatenation(char* chaine1 , char* chaine2);


#endif 