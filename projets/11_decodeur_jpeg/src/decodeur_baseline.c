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
#include "../include/decodeur_baseline.h"
#include "../include/matrice.h"
#include "../include/bloc_8_fois_8.h"
#include "../include/sur_échantiollnnage.h"






/*---------------------- Decodeur baseline : MODE SEQUENTIELLE -----------------*/

void decodeur_baseline(char* nom_fichier )
{
  /*--------------------  ETAPE I : Extraction des donnes : -------------*/


  /*---------On fait la redriction de la commande :hexdump -C -v nom_fichier > entete_jpeg.txt---- */

  char commande[100];
  sprintf(commande,"hexdump -C -v  %s > entete_jpeg.txt ",nom_fichier);
  system(commande); 

    
  /*--------------------On extracte l'entete de : entete_jpeg.txt vers tete.txt ---------------*/ 

  FILE* fichier0 =fopen("entete_jpeg.txt", "r");
  redriction_entete_jpeg(fichier0,"tete.txt");

    
  /* -------------------- On initialise les tab_chaine des differents sections---------------- -*/

  tab_chaine SOFO={0,NULL} ;  /* marquer: c0*/
  tab_chaine SOS={0,NULL} ;  /* marquer: da*/
  tab_chaine APPO={0,NULL} ;  /* marquer: e0*/
  tab_chaine DQT={0,NULL} ;  /* marquer: db*/
  tab_chaine DHT={0,NULL} ;  /* marquer: c4*/
  tab_chaine COM = {0,NULL}; /* marquer : fe*/
    

  /*------------------------- On ouvrir le fichier : tete.txt---------------------------- */

  FILE* fichier=fopen("tete.txt","r");
  
  char* octet=NULL;
  octet=malloc(sizeof(char)*3);
  octet[0]=fgetc(fichier);
  octet[1]=fgetc(fichier);
  octet[2]='\0'; /* On marque le fin de chaine */
    
  octet_suivant(octet,fichier); /* on avance vers l'ocete suivant : d8(debut de l'image)*/

  if(strcmp(octet,"d8")!=0)
  {
    fprintf(stderr, "Votre fichier n'est pas une fichier jpeg\n");
    exit(1);   
  }
     
  /*---------------------- On remplir les tab_chaine des #ts sections : ---------------------------- */

  extraction_sections(fichier,octet,&SOFO,&SOS,&APPO,&DQT,&DHT,&COM);

  /*-------------------- extractions des differents informations pour le decodage --------------------*/

  tab_chaine taille = taille_image(SOFO);
  tab_chaine image_jpeg =  extraction_image(SOS);
  int nombres_comp = nombres_composantes(SOFO);
    
    
  /*--------------- Initialisation des donnees -------------*/
  tab_chaine tab_huffman_Y_DC = {0,NULL};
  tab_chaine tab_huffman_Y_AC = {0,NULL};
  tab_chaine tab_quantification_Y = {0,NULL};
  tab_chaine decode_huffman_Y_DC = {0,NULL};
  tab_chaine decode_huffman_Y_AC = {0,NULL};

  tab_chaine tab_huffman_Cb_Cr_DC = {0,NULL};
  tab_chaine tab_huffman_Cb_Cr_AC = {0,NULL};
  tab_chaine tab_quantification_Cb_Cr = {0,NULL};
  tab_chaine decode_huffman_Cb_Cr_DC = {0,NULL};
  tab_chaine decode_huffman_Cb_Cr_AC = {0,NULL};




  /*----------------------  Transformation de l'image en binaires :----------------------------------*/
    
  char* image_en_bin = transformatin_image_en_binnaire(image_jpeg);

  if(nombres_comp==1)
  {
    /* il s'agit d'une image pgm */

    /*------------- Extraction des tables de Huffman -----------*/
    tab_huffman_Y_DC = extracte_tab_huffamn("Y","DC",DHT,SOS,SOFO);
    tab_huffman_Y_AC = extracte_tab_huffamn("Y","AC",DHT,SOS,SOFO);

    /*---------------- Extraction des tables de Quantification ------------*/
    tab_quantification_Y = exctracte_table_quantification("Y",DQT,SOFO);

    /*---------------- Decodage de tables de Huffmman ----------------------*/
    decode_huffman_Y_DC = decodage_tab_huffman(tab_huffman_Y_DC );
    decode_huffman_Y_AC = decodage_tab_huffman(tab_huffman_Y_AC);

  }
  else
  {
    /* il s'agit d'une image ppm */

    /*------------- Extraction des tables de Huffman -----------*/
    tab_huffman_Y_DC = extracte_tab_huffamn("Y","DC",DHT,SOS,SOFO);
    tab_huffman_Y_AC = extracte_tab_huffamn("Y","AC",DHT,SOS,SOFO);
    tab_huffman_Cb_Cr_DC = extracte_tab_huffamn("Cb","DC",DHT,SOS,SOFO);
    tab_huffman_Cb_Cr_AC = extracte_tab_huffamn("Cb","AC",DHT,SOS,SOFO);

    /*---------------- Extraction des tables de Quantification ------------*/
    tab_quantification_Y = exctracte_table_quantification("Y",DQT,SOFO);
    tab_quantification_Cb_Cr = exctracte_table_quantification("Cb",DQT,SOFO);

    /*-------------------- Decodage des tables de Huffman ----------------------*/
    decode_huffman_Y_DC = decodage_tab_huffman(tab_huffman_Y_DC );
    decode_huffman_Y_AC = decodage_tab_huffman(tab_huffman_Y_AC);
    decode_huffman_Cb_Cr_DC = decodage_tab_huffman(tab_huffman_Cb_Cr_DC );
    decode_huffman_Cb_Cr_AC = decodage_tab_huffman(tab_huffman_Cb_Cr_AC);






  }
  

 

  /*-----------------------------------  On commance le travaille :  --------------------------------- */

  int DC_precedent = 0 ;
  int compteur = 0 ; 
  char* nom_fichier_ppm = recupere_nom_ppm(nom_fichier,nombres_comp);

  int hauteur_image = convert_octet_to_uint16_t(taille.pointeur[0]);
  int largeur_image = convert_octet_to_uint16_t(taille.pointeur[1]);
       
  if(nombres_comp==1)
  {
    /* il s'agit d'une image pgm */
    
    MCU_BLOC* image = NULL ;
  
    FILE* fich = fopen(nom_fichier_ppm, "w");

    fprintf(fich, "P5\n%d %d\n255\n", largeur_image,hauteur_image);
        


  

    remplissage_image_gris(fich ,&image,largeur_image,hauteur_image,image_en_bin,decode_huffman_Y_DC,decode_huffman_Y_AC,&DC_precedent,&compteur,tab_quantification_Y);

    fclose(fich);


  }
  else
  {
    /* il s'agit d'une image ppm */

    int DC_precedant_Y = 0 ;
    int DC_precedant_Cb = 0 ;
    int DC_precedant_Cr = 0 ;

    /*  on stocke toute le mcu dans une liste chaine */
    liste_chaine_mcu* image = NULL ;


    FILE* fich = fopen(nom_fichier_ppm, "w");

    fprintf(fich, "P6\n%d %d\n255\n", largeur_image,hauteur_image);
    
    remplissage_image_couleur(fich , &image,  largeur_image , hauteur_image ,  image_en_bin , decode_huffman_Y_DC ,   decode_huffman_Y_AC ,  decode_huffman_Cb_Cr_DC ,  decode_huffman_Cb_Cr_AC ,      &DC_precedant_Y , &DC_precedant_Cb , &DC_precedant_Cr ,   &compteur , tab_quantification_Y ,  tab_quantification_Cb_Cr ,  SOFO ,  SOS );

    fclose(fich);


  }








  /* ----------------------------- apres si on termine : on clean every things-------------------------- */

  /* ---------------------------------------on ferme les fichiers :--------------------------------- */

  fclose(fichier0); /*On ferme le fichier  : entete_jpeg.txt*/
  fclose(fichier);  /*On ferme le fichier : tete.txt */
    
  /*----------------- On libere l'espace memoire--------------------------------------------*/

  if(nombres_comp==1)
  {
    liberer_tab_chaine(&SOFO);
    liberer_tab_chaine(&SOS);
    liberer_tab_chaine(&APPO);
    liberer_tab_chaine(&DQT);
    liberer_tab_chaine(&DHT);
    liberer_tab_chaine(&COM);
    liberer_tab_chaine(&taille);
    liberer_tab_chaine(&image_jpeg);

    liberer_tab_chaine(&tab_huffman_Y_DC);
    liberer_tab_chaine(&tab_huffman_Y_AC);
    liberer_tab_chaine(&tab_quantification_Y);
    liberer_tab_chaine(&decode_huffman_Y_DC);
    liberer_tab_chaine(&decode_huffman_Y_AC);
  }
  else
  {
    liberer_tab_chaine(&SOFO);
    liberer_tab_chaine(&SOS);
    liberer_tab_chaine(&APPO);
    liberer_tab_chaine(&DQT);
    liberer_tab_chaine(&DHT);
    liberer_tab_chaine(&COM);
    liberer_tab_chaine(&taille);
    liberer_tab_chaine(&image_jpeg);

    liberer_tab_chaine(&tab_huffman_Y_DC);
    liberer_tab_chaine(&tab_huffman_Y_AC);
    liberer_tab_chaine(&tab_quantification_Y);
    liberer_tab_chaine(&decode_huffman_Y_DC);
    liberer_tab_chaine(&decode_huffman_Y_AC);

    liberer_tab_chaine(&tab_huffman_Cb_Cr_DC);
    liberer_tab_chaine(&tab_huffman_Cb_Cr_AC);
    liberer_tab_chaine(&tab_quantification_Cb_Cr);
    liberer_tab_chaine(&decode_huffman_Cb_Cr_DC);
    liberer_tab_chaine(&decode_huffman_Cb_Cr_AC);

  }




  /* ------------on libere l'espace memoire de : octet ,image_en_bin et nom_fichier_ppm ----------------*/

  free(octet);
  free(image_en_bin);
  free(nom_fichier_ppm);


  /* ---------------------------On supprime le fichier .txt-----------------------------*/
    
  remove("entete_jpeg.txt");
  // Pour le fichier tete.txt n'est pas necessaire d'etre supprimer car On l'ouvrir avce mode "w".
  remove("tete.txt");

}






/*------------- fonction pour recupere le nom de fichier ppm --------------------------*/

char* recupere_nom_ppm(char* nom_fichier , int nb_comp)
{
  /*----------------------- recuperation de nom de la fichier ------------------------*/

  char* nom_fichier_ppm = NULL;


  int taille = 0 ;
  
  if(nom_fichier[strlen(nom_fichier)-2]=='e')
  {
    nom_fichier_ppm = malloc(sizeof(char)*(strlen(nom_fichier)));
    nom_fichier_ppm[strlen(nom_fichier)-1]='\0';
    
    taille = strlen(nom_fichier)-4;
  }
  else
  {
    nom_fichier_ppm = malloc(sizeof(char)*(strlen(nom_fichier)+1));
    nom_fichier_ppm[strlen(nom_fichier)]='\0';

    taille = strlen(nom_fichier)-3;

  }
 
  int ptr = 0;
  for( ptr=0 ; ptr<taille;ptr++)
  {
    nom_fichier_ppm[ptr]=nom_fichier[ptr];
  }
  

 if(nb_comp==1)
 {

 /* si le nb_comp=1 donc image gris :.pgm*/

  nom_fichier_ppm[ptr]='p';
  ptr++;

  nom_fichier_ppm[ptr]='g';
  ptr++;

  nom_fichier_ppm[ptr]='m';

 }
 else
 {
  /* si non il s'agit d'une image avec couleur : .ppm*/

  nom_fichier_ppm[ptr]='p';
  ptr++;

  nom_fichier_ppm[ptr]='p';
  ptr++;

  nom_fichier_ppm[ptr]='m';
 }


  return nom_fichier_ppm;
    
}



void traite_bloc(bloc_8_fois_8* bloc , char* image_en_bin, tab_chaine decode_huffman_Y_DC ,tab_chaine decode_huffman_Y_AC ,int* DC_precedent, int* compteur, tab_chaine tab_quant)
{

  /* decodage de bloc */

  decodage_image_Huffman(image_en_bin,decode_huffman_Y_DC, decode_huffman_Y_AC, bloc->data_vect_64,DC_precedent, compteur);
  
  /* quantification inverse :*/

  quantification_inverse(bloc->data_vect_64,tab_quant);


  /* zig_zag inverse : */

  zig_zag_inverse(bloc->data_vect_64,bloc->data_mat);



  /* IDCT : */

  int matrice_sortie[8][8];

  idct_rapide(bloc->data_mat, matrice_sortie);

  for(int i=0 ; i<8;i++)
  {
    for(int j=0 ; j<8;j++)
    {
      bloc->data_mat[i][j]=matrice_sortie[i][j];
            
    }
  }


}


void traite_mcu(liste_chaine_mcu** image, mcu_vect *mcu_flux, char *image_en_bin, tab_chaine tab_Hufffman_Y_DC, tab_chaine tab_Hufffman_Y_AC, tab_chaine tab_Hufffman_Cb_Cr_DC, tab_chaine tab_Hufffman_Cb_Cr_AC, tab_chaine SOS, tab_chaine SOFO, int *compteur, int *DC_precedent_Y, int *DC_prcedent_Cb, int *DC_precednt_Cr, tab_chaine tab_quant_Y, tab_chaine tab_quant_Cb_Cr )
{

  /* cette fonction traite une MCU de deocdage jusque YCbCr_vers_RGB  */

  /*--------------------- Decodage de MCU :   ---------------------------*/

    
  decodage_Huffman_mcu(mcu_flux, image_en_bin, tab_Hufffman_Y_DC, tab_Hufffman_Y_AC, tab_Hufffman_Cb_Cr_DC, tab_Hufffman_Cb_Cr_AC, SOS, SOFO, compteur, DC_precedent_Y, DC_prcedent_Cb, DC_precednt_Cr);

  
  /*----------------------- quantification -----------------------------*/
  
  // qunatification inverse de Y

  MCU_BLOC* data_Y = mcu_flux->data_vect_Y;

  while (data_Y != NULL)
  {
    quantification_inverse(data_Y->bloc.data_vect_64, tab_quant_Y);
    data_Y = data_Y->suiv;
  }

  // qunatification inverse de Cb

  MCU_BLOC *data_Cb = mcu_flux->data_vect_Cb;

  while (data_Cb != NULL)
  {
    quantification_inverse(data_Cb->bloc.data_vect_64, tab_quant_Cb_Cr);
    data_Cb = data_Cb->suiv;
  }

    // qunatification inverse de Cr

    MCU_BLOC *data_Cr = mcu_flux->data_vect_Cr;

    while (data_Cr != NULL)
    {
      quantification_inverse(data_Cr->bloc.data_vect_64, tab_quant_Cb_Cr);
      data_Cr = data_Cr->suiv;
    }

    /*---------------------------- zig_zag inverese -------------------------*/

    // zig_zag inverse de Y

    data_Y = mcu_flux->data_vect_Y;

    while (data_Y != NULL)
    {
      zig_zag_inverse(data_Y->bloc.data_vect_64, data_Y->bloc.data_mat);
      data_Y = data_Y->suiv;
    }

    // zig_zag inverse de Cb

    data_Cb = mcu_flux->data_vect_Cb;

    while (data_Cb != NULL)
    {
      zig_zag_inverse(data_Cb->bloc.data_vect_64, data_Cb->bloc.data_mat);
      data_Cb = data_Cb->suiv;
    }

    // zig_zag  inverse de Cr

    data_Cr = mcu_flux->data_vect_Cr;

    while (data_Cr != NULL)
    {
      zig_zag_inverse(data_Cr->bloc.data_vect_64, data_Cr->bloc.data_mat);
      data_Cr = data_Cr->suiv;
    }

    /*---------------------- IDCT ------------------------------ */
    
    // IDCT de Y

    data_Y = mcu_flux->data_vect_Y;

    while (data_Y != NULL)
    {

      int mat_sortie_idct[8][8];
      idct_rapide(data_Y->bloc.data_mat, mat_sortie_idct);

      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          data_Y->bloc.data_mat[i][j] = mat_sortie_idct[i][j];
        }
      }
        
      data_Y = data_Y->suiv;

    }

    // IDCT de Cb

    data_Cb = mcu_flux->data_vect_Cb;

    while (data_Cb != NULL)
    {
      int mat_sortie_idct[8][8];
      idct_rapide(data_Cb->bloc.data_mat, mat_sortie_idct);
        
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          data_Cb->bloc.data_mat[i][j] = mat_sortie_idct[i][j];
            
        }
        
      }
        
      data_Cb = data_Cb->suiv;

    }

    // IDCT de Cr

   data_Cr = mcu_flux->data_vect_Cr;

    while (data_Cr != NULL)
    {
      int mat_sortie_idct[8][8];
      idct_rapide(data_Cr->bloc.data_mat, mat_sortie_idct);

      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          data_Cr->bloc.data_mat[i][j] = mat_sortie_idct[i][j];
            
        }
        
      }

        
      data_Cr = data_Cr->suiv;
    }

    /*------------------ SURéchantillonnage ----------------------------*/

 
    matrice Y ;
    Y.pointeur = NULL ;
  
    matrice Cb ;
    Cb.pointeur = NULL ;

    matrice Cr ;
    Cr.pointeur = NULL ;

    mcu_mat  mcu ={ Y , Cb , Cr} ;

    data_vect_vers_data_mat(*mcu_flux, &mcu, SOFO);

    sur_echantiollnnage(&mcu);

    /*------------- YCbCr vers RGB ----------------------------*/

    YCbCr_RGB(mcu);

    /*---------------- Insere le mcu dans  liste chaine ------------*/

    inserer_liste_chaine_mcu(image, mcu);

}



void remplissage_image_gris(FILE* fichier, MCU_BLOC** image, int largeur_image , int hauteur_image , char* image_en_bin ,tab_chaine decode_huffman_Y_DC , tab_chaine  decode_huffman_Y_AC ,int* DC_precedent,  int* compteur,tab_chaine tab_quantification_Y)
{


  int nb_bloc_hrz = largeur_image/8 ; 
  int nb_bloc_vert = hauteur_image/8 ;

  int res_dte =  largeur_image - nb_bloc_hrz*8 ;
  int res_bas =  hauteur_image - nb_bloc_vert*8 ;

  int nb_bloc_hrz_tronc = nb_bloc_hrz;

  if(res_dte!=0)
  {
    nb_bloc_hrz_tronc +=1; 

  }

  if(res_bas!=0)
  {
    nb_bloc_vert +=1; 

  }
  
  // uint8_t matrice_image[(const int )hauteur_image][(const int )largeur_image];

  matrice mat_image;
  mat_image.pointeur = NULL;
  initialiser_matrice(&mat_image , hauteur_image,largeur_image );
  




  for(int y=0 ; y < nb_bloc_vert ; y++)
  {

    /*----------------------- lecture des donnes --------------------*/

    for(int x=0 ; x < nb_bloc_hrz_tronc ; x++)
    {
      bloc_8_fois_8 bloc ;
      bloc.position_x = x;
      bloc.position_y = y ;

      
      
      traite_bloc( &bloc ,image_en_bin,decode_huffman_Y_DC , decode_huffman_Y_AC , DC_precedent, compteur, tab_quantification_Y);
      inserer_mcu(image,bloc);

    }
  

    
  /*-------------------- ecriture  des donnes   : ---------------------------*/

    MCU_BLOC* copie_image_1 = *image ;

    MCU_BLOC* copie_image2 = copie_image_1 ;

    int stop_y = 8 ;

    if(res_bas!=0 && y==nb_bloc_vert-1)
    {
      stop_y = hauteur_image%8;
    }

    for(int j=0 ; j<stop_y ; j++)
    {

      copie_image2 = copie_image_1 ;

      int stop_x= 8 ;
      for(int x=0 ; x<nb_bloc_hrz_tronc; x++)
      {
                  
        if(x==nb_bloc_hrz)
        {
          stop_x = largeur_image%8;

        }
            
        
        for(int i =0 ; i<stop_x ; i++)
        {
          // matrice_image[8*y + j][8*x +i ] = copie_image2->bloc.data_mat[j][i];
          ajouter_elem(&mat_image, copie_image2->bloc.data_mat[j][i], 8*y + j,8*x +i );

        }

        copie_image2=copie_image2->suiv ;
                  


      }

    }

    liberer_mcu(image);
    *image=NULL;
        
        
  }

  

  /*-------------------- l'écriture finale dans le fichier ---------------------------*/

  // fwrite(matrice_image,sizeof(uint8_t),hauteur_image*largeur_image,fichier);

  for(int i=0 ; i<hauteur_image;i++)
  {
    for(int j=0 ; j<largeur_image ; j++ )
    {
      fprintf(fichier,"%c",(uint8_t)mat_image.pointeur[i][j]);
    }
    
  }
  
  /*------------------- libération des donneés -------------------------*/

  
  liberer_matrice(&mat_image);

} 


void remplissage_image_couleur(FILE* fichier , liste_chaine_mcu** image, int largeur_image , int hauteur_image , char* image_en_bin ,tab_chaine decode_huffman_Y_DC , tab_chaine  decode_huffman_Y_AC , tab_chaine deocde_huffman_Cb_Cr_DC , tab_chaine deocde_huffman_Cb_Cr_AC ,     int* DC_precedant_Y , int *DC_precedant_Cb ,int* DC_precedant_Cr ,  int* compteur ,tab_chaine tab_quant_Y , tab_chaine tab_quant_Cb_Cr , tab_chaine SOFO , tab_chaine SOS )
{

  tab_chaine info_Y = extracte_info_composante("Y",SOFO);
  int hy = convert_nibble_to_uint8_t(info_Y.pointeur[1][0]); 
  int vy = convert_nibble_to_uint8_t(info_Y.pointeur[1][1]);

  liberer_tab_chaine(&info_Y);



  int nb_bloc_hrz = largeur_image/(hy*8) ; 
  int nb_bloc_vert = hauteur_image/(vy*8) ;

  int res_dte =  largeur_image%(hy*8);
  int res_bas =  hauteur_image%(vy*8) ;

  int nb_bloc_hrz_tronc = nb_bloc_hrz;

  if(res_dte!=0)
  {
    nb_bloc_hrz_tronc +=1; 

  } 


  if(res_bas!=0)
  {
    nb_bloc_vert +=1; 

  }




  matrice mat_Y ;
  mat_Y.pointeur = NULL ;

  initialiser_matrice(&mat_Y,hauteur_image,largeur_image);

  matrice mat_Cb ;
  mat_Cb.pointeur = NULL ;

  initialiser_matrice(&mat_Cb,hauteur_image,largeur_image);

  matrice mat_Cr ;
  mat_Cr.pointeur = NULL ;

  initialiser_matrice(&mat_Cr,hauteur_image,largeur_image);

 




  for(int y=0 ; y < nb_bloc_vert ; y++)
  {

    /*------------------- lecture des donnes --------------------*/

    for(int x=0 ; x < nb_bloc_hrz_tronc ; x++) 
    {
      MCU_BLOC* data_vect_Y = NULL ;
      MCU_BLOC* data_vect_Cb = NULL ;
      MCU_BLOC* data_vect_Cr = NULL ;

      mcu_vect mcu_vect_bloc ={data_vect_Y,data_vect_Cb,data_vect_Cr};
 
      traite_mcu(image,&mcu_vect_bloc,image_en_bin,decode_huffman_Y_DC,decode_huffman_Y_AC,deocde_huffman_Cb_Cr_DC,deocde_huffman_Cb_Cr_AC, SOS ,SOFO ,compteur ,DC_precedant_Y,DC_precedant_Cb,DC_precedant_Cr,tab_quant_Y,tab_quant_Cb_Cr);



    }
        
        
  


  /*------------------  ecriture des données ---------------------------*/


    liste_chaine_mcu* copie_image_1 = *image ;

    liste_chaine_mcu* copie_image2 = copie_image_1 ;


    int stop_y = vy*8 ;

    if(res_bas!=0 && y==nb_bloc_vert-1)
    {
      stop_y = hauteur_image%(vy*8);
    }
        
    for(int j=0 ; j < stop_y ; j++)
    {

      copie_image2 = copie_image_1 ;

      int stop_x= hy*8 ;

      for(int x=0 ; x<nb_bloc_hrz_tronc; x++)
      {
                  
        if(x==nb_bloc_hrz)
        {
          stop_x = largeur_image%(hy*8);

        }



        for(int i =0 ; i<stop_x ; i++)
        {


          ajouter_elem(&mat_Y,copie_image2->data.data_Y.pointeur[j][i],vy*y*8 + j,8*x*hy +i);
          ajouter_elem(&mat_Cb,copie_image2->data.data_Cb.pointeur[j][i],vy*y*8 + j,8*x*hy +i);
          ajouter_elem(&mat_Cr,copie_image2->data.data_Cr.pointeur[j][i],vy*y*8 + j,8*x*hy +i);



        }
                
        
        copie_image2=copie_image2->suiv ;
                  


      }

    }

    liberer_liste_chaine_mcu(image);
    *image = NULL ;






  }


  /*---------------------- l'ecriture finale dans le fichier -------------------*/

  for(int i=0 ; i<hauteur_image;i++)
  {
    for(int j=0 ; j<largeur_image ; j++ )
    {
      fprintf(fichier,"%c%c%c",(uint8_t)mat_Y.pointeur[i][j],(uint8_t)mat_Cb.pointeur[i][j],(uint8_t)mat_Cr.pointeur[i][j]);
    }
    
  }

  
  /*------------------- libération des donneés -------------------------*/

  liberer_matrice(&mat_Y);
  liberer_matrice(&mat_Cb);
  liberer_matrice(&mat_Cr);

}
























































