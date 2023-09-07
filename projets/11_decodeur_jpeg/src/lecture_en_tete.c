#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/tab_chaine.h"
#include "../include/lecture_en_tete.h"
#include "../include/decodage_Huffman.h"

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE I DU MODULE : Récuperation de l'entete_jpeg.
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* -------------------------------------extracte l'entete_jpeg et le mettre dans  le fichier : tete.txt-------------------------  */

void redriction_entete_jpeg(FILE *fichier, char *nom_fich)
{
    FILE *fich_entete = fopen(nom_fich, "w");

    fseek(fichier, 10, SEEK_SET);
    char lettre = fgetc(fichier);

    int code_ascii_bare = 124;              /* code asci de bare verticale '|'*/
    char fin_ligne = (char)code_ascii_bare; /* fin_ligne='|'*/

    int code_ascii_espace = 32;            /* code asci de l'espace ' '*/
    char espace = (char)code_ascii_espace; /* espace =' '*/

    while (lettre != EOF)
    {
        if (lettre != espace && lettre != fin_ligne)
        {
            fputc(lettre, fich_entete);
            lettre = fgetc(fichier);
        }
        else
        {
            if (lettre == espace)
            {
                lettre = fgetc(fichier);
            }
            else
            {
                fseek(fichier, 26, SEEK_CUR);
                lettre = fgetc(fichier);
            }
        }
    }
    fclose(fich_entete);
}

/*------------------------------------------extraction_sections : ---------------------------------------------------------------------------*/

void extraction_sections(FILE *fichier, char *octet, tab_chaine *p_SOFO, tab_chaine *p_SOS, tab_chaine *p_APPO, tab_chaine *p_DQT, tab_chaine *p_DHT, tab_chaine *p_COM)
{

    if (strcmp(octet, "d8") == 0)
    {
        /* section SOI :  debut de l''image  */
        octet_suivant(octet, fichier); /*  on lit ff */
        octet_suivant(octet, fichier); /* le marquer suivant */

        extraction_sections(fichier, octet, p_SOFO, p_SOS, p_APPO, p_DQT, p_DHT, p_COM);
    }
    else if (strcmp(octet, "c0") == 0)
    {

        /* section SOFO */
        octet_suivant(octet, fichier);
        lectrue_section_SOFO(fichier, octet, p_SOFO, p_SOS, p_APPO, p_DQT, p_DHT, p_COM);
    }
    else if (strcmp(octet, "da") == 0)
    {
        /* section S0S */
        octet_suivant(octet, fichier);
        lectrue_section_SOS(fichier, octet, p_SOFO, p_SOS, p_APPO, p_DQT, p_DHT, p_COM);
    }
    else if (strcmp(octet, "db") == 0)
    {
        /* section DQT */
        octet_suivant(octet, fichier);
        lectrue_section_DQT(fichier, octet, p_SOFO, p_SOS, p_APPO, p_DQT, p_DHT, p_COM);
    }
    else if (strcmp(octet, "e0") == 0)
    {
        /* section APPO */
        octet_suivant(octet, fichier);
        lectrue_section_APPO(fichier, octet, p_SOFO, p_SOS, p_APPO, p_DQT, p_DHT, p_COM);
    }
    else if (strcmp(octet, "c4") == 0)
    {
        /* section DHT */
        octet_suivant(octet, fichier);
        lectrue_section_DHT(fichier, octet, p_SOFO, p_SOS, p_APPO, p_DQT, p_DHT, p_COM);
    }
    else if (strcmp(octet, "fe") == 0)
    {
        /* section COM : */
        octet_suivant(octet, fichier);
        lectrue_section_COM(fichier, octet, p_SOFO, p_SOS, p_APPO, p_DQT, p_DHT, p_COM);
    }
    else
    {

        /*il nous reste que le derniere marquere EOI : d9*/
        /* section EOI : On s'arrete */
    }
}

/*----------------------------------------------fonction d'extractino de la section SOFO ---------------------------------------*/

void lectrue_section_SOFO(FILE *fichier, char *octet, tab_chaine *p_SOFO, tab_chaine *p_SOS, tab_chaine *p_APP0, tab_chaine *p_DQT, tab_chaine *p_DHT, tab_chaine *p_COM)
{

    while (strcmp(octet, "ff") != 0)
    {
        ajouter_chaine(p_SOFO, octet);
        octet_suivant(octet, fichier);
    }

    if (strcmp(octet, "ff") == 0)
    {
        octet_suivant(octet, fichier);
        if (valide_section(octet) == 1)
        {
            extraction_sections(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
        else
        {
            /*on ajout ff tout d'abord */
            ajouter_chaine(p_SOFO, "ff");
            /* et apres on ajout octet */
            ajouter_chaine(p_SOFO, octet);
            /*On relance lectrure_section_SOFO */
            octet_suivant(octet, fichier);
            lectrue_section_SOFO(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
    }
}

/*--------------------------------------------- fonction d'extraction de la section SOS --------------------------------------------------*/

void lectrue_section_SOS(FILE *fichier, char *octet, tab_chaine *p_SOFO, tab_chaine *p_SOS, tab_chaine *p_APP0, tab_chaine *p_DQT, tab_chaine *p_DHT, tab_chaine *p_COM)
{

    while (strcmp(octet, "ff") != 0)
    {
        ajouter_chaine(p_SOS, octet);
        octet_suivant(octet, fichier);
    }

    if (strcmp(octet, "ff") == 0)
    {
        octet_suivant(octet, fichier);
        if (valide_section(octet) == 1)
        {
            extraction_sections(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
        else
        {
            /*on ajout ff tout d'abord */
            ajouter_chaine(p_SOS, "ff");
            /* et apres on ajout octet */
            if (strcmp(octet, "00") != 0)
            {
                /* si c'est n' est pas le byte stuffing : On le recupere  : */
                ajouter_chaine(p_SOS, octet);
            }

            /*On relance lectrure_section_SOFO */
            octet_suivant(octet, fichier);
            lectrue_section_SOS(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
    }
}

/*---------------------------------------fonction d'extraction de la section DQT-------------------------------------------------------------------------------*/

void lectrue_section_DQT(FILE *fichier, char *octet, tab_chaine *p_SOFO, tab_chaine *p_SOS, tab_chaine *p_APP0, tab_chaine *p_DQT, tab_chaine *p_DHT, tab_chaine *p_COM)
{

    while (strcmp(octet, "ff") != 0)
    {
        ajouter_chaine(p_DQT, octet);

        octet_suivant(octet, fichier);
    }

    if (strcmp(octet, "ff") == 0)
    {
        octet_suivant(octet, fichier);
        if (valide_section(octet) == 1)
        {

            extraction_sections(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
        else
        {
            /*on ajout ff tout d'abord */
            ajouter_chaine(p_DQT, "ff");
            /* et apres on ajout octet */
            ajouter_chaine(p_DQT, octet);
            /*On relance lectrure_section_SOFO */
            octet_suivant(octet, fichier);
            lectrue_section_DQT(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
    }
}

/*---------------------------------------fonction d'extraction de la section APP0 -------------------------------------------------------------------------------*/

void lectrue_section_APPO(FILE *fichier, char *octet, tab_chaine *p_SOFO, tab_chaine *p_SOS, tab_chaine *p_APP0, tab_chaine *p_DQT, tab_chaine *p_DHT, tab_chaine *p_COM)
{

    while (strcmp(octet, "ff") != 0)
    {
        ajouter_chaine(p_APP0, octet);
        octet_suivant(octet, fichier);
    }

    if (strcmp(octet, "ff") == 0)
    {
        octet_suivant(octet, fichier);
        if (valide_section(octet) == 1)
        {
            extraction_sections(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
        else
        {
            /*on ajout ff tout d'abord */
            ajouter_chaine(p_APP0, "ff");
            /* et apres on ajout octet */
            ajouter_chaine(p_APP0, octet);
            /*On relance lectrure_section_APPO */
            octet_suivant(octet, fichier);
            lectrue_section_APPO(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
    }
}

/*---------------------------------------fonction d'extraction de la section DHT-------------------------------------------------------------------------------*/

void lectrue_section_DHT(FILE *fichier, char *octet, tab_chaine *p_SOFO, tab_chaine *p_SOS, tab_chaine *p_APP0, tab_chaine *p_DQT, tab_chaine *p_DHT, tab_chaine *p_COM)
{

    while (strcmp(octet, "ff") != 0)
    {

        ajouter_chaine(p_DHT, octet);

        octet_suivant(octet, fichier);
    }

    if (strcmp(octet, "ff") == 0)
    {
        octet_suivant(octet, fichier);
        if (valide_section(octet) == 1)
        {
            extraction_sections(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
        else
        {
            /*on ajout ff tout d'abord */
            ajouter_chaine(p_DHT, "ff");
            /* et apres on ajout octet */
            ajouter_chaine(p_DHT, octet);
            /*On relance lectrure_section_DHT */
            octet_suivant(octet, fichier);
            lectrue_section_DHT(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
    }
}

/*---------------------------------------fonction d'extraction de la section COM :-------------------------------------------------------------------------------*/

void lectrue_section_COM(FILE *fichier, char *octet, tab_chaine *p_SOFO, tab_chaine *p_SOS, tab_chaine *p_APP0, tab_chaine *p_DQT, tab_chaine *p_DHT, tab_chaine *p_COM)
{

    while (strcmp(octet, "ff") != 0)
    {

        ajouter_chaine(p_COM, octet);

        octet_suivant(octet, fichier);
    }

    if (strcmp(octet, "ff") == 0)
    {
        octet_suivant(octet, fichier);
        if (valide_section(octet) == 1)
        {
            extraction_sections(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
        else
        {
            /*on ajout ff tout d'abord */
            ajouter_chaine(p_COM, "ff");
            /* et apres on ajout octet */
            ajouter_chaine(p_COM, octet);
            /*On relance lectrure_section_COM */
            octet_suivant(octet, fichier);
            lectrue_section_COM(fichier, octet, p_SOFO, p_SOS, p_APP0, p_DQT, p_DHT, p_COM);
        }
    }
}

/*-------------------------------------------------------------valide_section----------------------------------------------------------------------------*/
int valide_section(char *octet)
{

    if (strcmp(octet, "c0") == 0)
    {
        /* section SOFO*/
        return 1;
    }
    else if (strcmp(octet, "d8") == 0)
    {
        /* section SOI */
        return 1;
    }
    else if (strcmp(octet, "d9") == 0)
    {
        /* section EOI */
        return 1;
    }
    else if (strcmp(octet, "da") == 0)
    {
        /* section S0S */
        return 1;
    }
    else if (strcmp(octet, "db") == 0)
    {
        /* section DQT */
        return 1;
    }
    else if (strcmp(octet, "e0") == 0)
    {
        /* section APPO */
        return 1;
    }
    else if (strcmp(octet, "c4") == 0)
    {
        /* section DHT */
        return 1;
    }
    else if (strcmp(octet, "fe") == 0)
    {
        /* section COM :*/
        return 1;
    }
    else
    {
        /* ne correspond pas a une section */
        return 0;
    }
}

/*-------------------------------------------------------------octet_suivant-------------------------------------------------------*/

void octet_suivant(char *octet, FILE *fichier)
{
    octet[0] = fgetc(fichier);
    octet[1] = fgetc(fichier);
    octet[2] = '\0';
}

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE II DU MODULE : Extraction de differents infos a partir de l'entete_jpeg.
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* ---------------------------------------------------------SOFO----------------------------------------------------------------------------------------------*/

int nombres_composantes(tab_chaine SOFO)
{
    return atoi(SOFO.pointeur[7]);
}

tab_chaine taille_image(tab_chaine SOFO)
{
    /* taille de l'image se trouve dans :SOFO*/
    tab_chaine taille_image = {0, NULL};

    /* on remplir le tab_chaine :*/
    // 1ere  pour la hauteur : code sur 2 octet : SOFO[3] et SOFO[4]
    char *res1 = concatenation(SOFO.pointeur[3], SOFO.pointeur[4]);
    ajouter_chaine(&taille_image, res1);
    free(res1);

    // 2eme  pour la largeur : code sur 2 octet : SOFO[5] et SOFO[6]
    char *res2 = concatenation(SOFO.pointeur[5], SOFO.pointeur[6]);
    ajouter_chaine(&taille_image, res2);
    free(res2);

    return taille_image;
}

tab_chaine extracte_info_composante(char *composant, tab_chaine SOFO)
{
    /* cette fonction prend a l'entree : {Y ou Cb ou Cr} et retourn:
     ------> Son identifant .
     ------> Ces facteures d'echantillonages
     ------> et son indice dans la table de quantification
    SI il ya un errure :
       return {O,NULL}

    */

    int nombres_comp = atoi(SOFO.pointeur[7]); // le nombre des composantes

    if (strcmp(composant, "Y") == 0 || strcmp(composant, "Cb") == 0 || strcmp(composant, "Cr") == 0)
    {

        if (nombres_comp == 1)
        {
            if (strcmp(composant, "Y") == 0)
            {
                tab_chaine info_comp_Y = {0, NULL};
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[8]);  // Ic de Y
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[9]);  // hxv de Y
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[10]); // IQ de Y

                return info_comp_Y;
            }
            else
            {
                fprintf(stderr, "le nombre de composnte est 1 donc : Y  seule \n");
            }
        }

        if (nombres_comp == 2)
        {
            if (strcmp(composant, "Y") == 0)
            {
                tab_chaine info_comp_Y = {0, NULL};
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[8]);  // Ic de Y
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[9]);  // hxv de Y
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[10]); // IQ de Y

                return info_comp_Y;
            }
            else if (strcmp(composant, "Cb") == 0)
            {
                tab_chaine info_comp_Cb = {0, NULL};
                ajouter_chaine(&info_comp_Cb, SOFO.pointeur[11]); // Ic de Cb
                ajouter_chaine(&info_comp_Cb, SOFO.pointeur[12]); // hxv de Cb
                ajouter_chaine(&info_comp_Cb, SOFO.pointeur[13]); // IQ de Cb

                return info_comp_Cb;
            }
            else
            {
                fprintf(stderr, "le nombre de composnte est 2 donc : Y ou Cb  seule \n");
            }
        }

        if (nombres_comp == 3)
        {

            if (strcmp(composant, "Y") == 0)
            {
                tab_chaine info_comp_Y = {0, NULL};
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[8]);  // Ic de Y
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[9]);  // hxv de Y
                ajouter_chaine(&info_comp_Y, SOFO.pointeur[10]); // IQ de Y

                return info_comp_Y;
            }
            else if (strcmp(composant, "Cb") == 0)
            {
                tab_chaine info_comp_Cb = {0, NULL};
                ajouter_chaine(&info_comp_Cb, SOFO.pointeur[11]); // Ic de Cb
                ajouter_chaine(&info_comp_Cb, SOFO.pointeur[12]); // hxv de Cb
                ajouter_chaine(&info_comp_Cb, SOFO.pointeur[13]); // IQ de Cb

                return info_comp_Cb;
            }
            else
            {
                /* donc il reste le composant : Cr  */
                tab_chaine info_comp_Cr = {0, NULL};
                ajouter_chaine(&info_comp_Cr, SOFO.pointeur[14]); // Ic de Cr
                ajouter_chaine(&info_comp_Cr, SOFO.pointeur[15]); // hxv de Cr
                ajouter_chaine(&info_comp_Cr, SOFO.pointeur[16]); // IQ de Cr

                return info_comp_Cr;
            }
        }
    }
    else
    {
        fprintf(stderr, "Pour le bon Usage de la fonction extracte_info_composante : le composnate doit etre:{Y , Cb ou Cr}  \n");
    }

    tab_chaine tab_defaut = {0, NULL}; // si il y a un errure d'Usage

    return tab_defaut;
}

/*--------------------------------------------------------------------SOS--------------------------------------------------------------------------------*/

tab_chaine extraction_image(tab_chaine SOS)
{
    tab_chaine image_jpeg = {0, NULL};
    char *res = concatenation(SOS.pointeur[0], SOS.pointeur[1]);
    char *ptr = NULL;
    int taille_image = (int)strtol(res, &ptr, 16);

    for (int i = 0; i < SOS.taille - taille_image; i++)
    {
        ajouter_chaine(&image_jpeg, SOS.pointeur[taille_image + i]);
    }

    free(res);
    return image_jpeg;
}

char *extracte_indice_huffman(char *composante, tab_chaine SOS, tab_chaine SOFO)
{
    /*
     return les indices d'une composante(Y,Cb ou Cr) : "<I_h pour DC><I_h pour AC>"
     si non return : NULL(EN CAS D'ERRUERE  D'Usage)
    */

    // On recuprer le nombres des elements :
    int nombres_comp = atoi(SOS.pointeur[2]);

    tab_chaine info_comp = extracte_info_composante(composante, SOFO);
    assert(info_comp.pointeur != NULL); // On continue  si extracte_info_composante marche tres bien

    // On recupere l'identifaint de la compasanate.

    char identifiant_comp[2];
    identifiant_comp[0] = info_comp.pointeur[0][0];
    identifiant_comp[1] = info_comp.pointeur[0][1];

    if (nombres_comp == 1)
    {
        if (strcmp(SOS.pointeur[3], identifiant_comp) == 0)
        {

            liberer_tab_chaine(&info_comp);
            return SOS.pointeur[4];
        }
        else
        {
            fprintf(stderr, "il y a un seul composante : votre composante n'exsite pas \n");
        }
    }

    if (nombres_comp == 2)
    {
        if (strcmp(SOS.pointeur[3], identifiant_comp) == 0)
        {
            liberer_tab_chaine(&info_comp);
            return SOS.pointeur[4];
        }
        else if (strcmp(SOS.pointeur[5], identifiant_comp) == 0)
        {

            liberer_tab_chaine(&info_comp);
            return SOS.pointeur[6];
        }
        else
        {
            fprintf(stderr, "il y a deux  composante : votre composante n'exsite pas \n");
        }
    }

    if (nombres_comp == 3)
    {
        if (strcmp(SOS.pointeur[3], identifiant_comp) == 0)
        {

            liberer_tab_chaine(&info_comp);
            return SOS.pointeur[4];
        }
        else if (strcmp(SOS.pointeur[5], identifiant_comp) == 0)
        {

            liberer_tab_chaine(&info_comp);
            return SOS.pointeur[6];
        }
        else if (strcmp(SOS.pointeur[7], identifiant_comp) == 0)
        {

            liberer_tab_chaine(&info_comp);
            return SOS.pointeur[8];
        }
        else
        {
            fprintf(stderr, "il y a 3  composantes : votre composante n'exsite pas \n");
        }
    }

    // On libere le memoire  :

    liberer_tab_chaine(&info_comp);

    // si il ya  un errure  : On return NULL
    return "NULL";
}

/*---------------------------------------------------------------------DHT--------------------------------------------------------------------------*/

tab_chaine extracte_tab_huffamn(char *composante, char *type, tab_chaine DHT, tab_chaine SOS, tab_chaine SOFO)
{
    /*
    cette fonction prend a l'entree le nom d'une composante {Y,Cb ou Cr} et le type {DC ,AC} et retourn son tab de huffman
    en cas d'errure return {NULL , 0}
    */
    tab_chaine tab_huffman = {0, NULL};

    int nombres_compo = nombres_composantes(SOFO);

    // on recupere les idices des huffman de composante :"(I_h_DC)(I_h_AC)"
    char indices_huffman[2];
    indices_huffman[0] = extracte_indice_huffman(composante, SOS, SOFO)[0]; // I_h pour DC
    indices_huffman[1] = extracte_indice_huffman(composante, SOS, SOFO)[1]; // I_h pour AC
    assert(strcmp(indices_huffman, "NULL") != 0);                           // on continue si tout passe bien

    if (nombres_compo == 1)
    {
        // Dans le cas ou le nombre des comp est 1 : On a pas besion des indices de huffman car il n y a pas d'ambigute
        /* il existe deux tables de  huffman : tab_huffman_Y_DC et tab_huffman_AC */

        // On verifie tout d'abord que le symbole donne est bien  : Y
        if (strcmp(composante, "Y") != 0)
        {
            fprintf(stderr, "Mais le nombre des composante est 1 : il existe que Y et le nom de composante que vous avez donner n'est pas Y \n");

            return tab_huffman;
        }

        // On recupere le nombre des symobles pour le 1ere table : nombre_symoble_1ere_tab
        int nombre_symoble_1ere_tab = 0;

        for (int i = 0; i < 16; i++)
        {
            char *ptr = NULL; // est un pointeur blabla : initule(Dans notre cas) :où sera stockée l'adresse du premier caractère non converti de la chaîne
            nombre_symoble_1ere_tab += (int)strtol(DHT.pointeur[3 + i], &ptr, 16);
        }

        // On deux positions qui identifent les type(DC ou AC) : DHT.pointeur[2][0] ou DHT.pointeur[21+nombre_symoble_1ere_tab][0]

        if (strcmp(type, "DC") == 0)
        {

            if (DHT.pointeur[2][0] == '0')
            {
                // bah c'est ici le tab_huffman_Y_DC :
                // On ajoute les 16 octets : chaque Octet d'indice i donne les nombres des symboles code sur i
                for (int i = 0; i < 16; i++)
                {
                    ajouter_chaine(&tab_huffman, DHT.pointeur[3 + i]);
                }

                for (int j = 0; j < nombre_symoble_1ere_tab; j++)
                {
                    ajouter_chaine(&tab_huffman, DHT.pointeur[19 + j]);
                }

                return tab_huffman;
            }
            else
            {
                assert(DHT.pointeur[21 + nombre_symoble_1ere_tab][0] == '0');

                // bah c'est ici le tab_huffman_Y_DC :
                // On ajoute les 16 octets : chaque Octet d'indice i donne les nombres des symboles code sur i

                // Donc il faut compter aussi le nombre des symboles des 2 tab_huffman

                int nombre_symoble_2_eme_tab = 0;
                for (int i = 0; i < 16; i++)
                {
                    ajouter_chaine(&tab_huffman, DHT.pointeur[21 + nombre_symoble_1ere_tab + 1 + i]);
                    char *ptr;
                    nombre_symoble_2_eme_tab += (int)strtol(DHT.pointeur[21 + nombre_symoble_1ere_tab + 1 + i], &ptr, 16);
                }

                for (int j = 0; j < nombre_symoble_2_eme_tab; j++)
                {
                    ajouter_chaine(&tab_huffman, DHT.pointeur[21 + nombre_symoble_1ere_tab + 17 + j]);
                }

                return tab_huffman;
            }
        }
        else if (strcmp(type, "AC") == 0)
        {
            if (DHT.pointeur[2][0] == '1')
            {
                // bah c'est ici le tab_huffman_Y_AC :
                // On ajoute les 16 octets : chaque Octet d'indice i donne les nombres des symboles code sur i
                for (int i = 0; i < 16; i++)
                {
                    ajouter_chaine(&tab_huffman, DHT.pointeur[3 + i]);
                }

                for (int j = 0; j < nombre_symoble_1ere_tab; j++)
                {
                    ajouter_chaine(&tab_huffman, DHT.pointeur[19 + j]);
                }

                return tab_huffman;
            }
            else
            {
                assert(DHT.pointeur[21 + nombre_symoble_1ere_tab][0] == '1');
                // bah c'est ici le tab_huffman_Y_AC :
                // On ajoute les 16 octets : chaque Octet d'indice i donne les nombres des symboles code sur i

                // Donc il faut compter aussi le nombre des symboles des 2 tab_huffman
                int nombre_symoble_2_eme_tab = 0;
                for (int i = 0; i < 16; i++)
                {
                    ajouter_chaine(&tab_huffman, DHT.pointeur[21 + nombre_symoble_1ere_tab + 1 + i]);
                    char *ptr;
                    nombre_symoble_2_eme_tab += (int)strtol(DHT.pointeur[21 + nombre_symoble_1ere_tab + 1 + i], &ptr, 16);
                }

                for (int j = 0; j < nombre_symoble_2_eme_tab; j++)
                {
                    ajouter_chaine(&tab_huffman, DHT.pointeur[21 + nombre_symoble_1ere_tab + 17 + j]);
                }

                return tab_huffman;
            }
        }
        else
        {
            fprintf(stderr, "mais vous etes seurieux : il existe sailement deux type : AC ou DC \n");
        }
    }
    else
    {
        /*------------------------- Cas des couleures --------------------------*/

        // On recupere l'indiice extacelent de table de Huffman demande

        char indice_h = strcmp(type, "DC") == 0 ? indices_huffman[0] : indices_huffman[1];
        char indice_type = strcmp(type, "DC") == 0 ? '0' : '1';

        /*------- nb_symbole 1ere tab_Huffman ---------*/
        int nb_symbole_1 = 0;
        for (int i = 0; i < 16; i++)
        {
            char *ptr = NULL;
            nb_symbole_1 += (int)strtol(DHT.pointeur[3 + i], &ptr, 16);
        }

        /*------- nb_symbole 2eme tab_Huffman ---------*/
        int nb_symbole_2 = 0;
        for (int i = 0; i < 16; i++)
        {
            char *ptr = NULL;
            nb_symbole_2 += (int)strtol(DHT.pointeur[22 + nb_symbole_1 + i], &ptr, 16);
        }

        /*------- nb_symbole 3eme tab_Huffman ---------*/
        int nb_symbole_3 = 0;
        for (int i = 0; i < 16; i++)
        {
            char *ptr = NULL;
            nb_symbole_3 += (int)strtol(DHT.pointeur[41 + nb_symbole_1 + nb_symbole_2 + i], &ptr, 16);
        }

        /*------- nb_symbole 1ere tab_Huffman ---------*/
        int nb_symbole_4 = 0;
        for (int i = 0; i < 16; i++)
        {
            char *ptr = NULL;
            nb_symbole_4 += (int)strtol(DHT.pointeur[60 + nb_symbole_1 + nb_symbole_2 + nb_symbole_3 + i], &ptr, 16);
        }

        if (indice_h == DHT.pointeur[2][1] && DHT.pointeur[2][0] == indice_type)
        {
            // On recupére le nb_symbole_1 de tab_Huffman :

            for (int i = 0; i < 16; i++)
            {
                ajouter_chaine(&tab_huffman, DHT.pointeur[3 + i]);
            }

            for (int j = 0; j < nb_symbole_1; j++)
            {
                ajouter_chaine(&tab_huffman, DHT.pointeur[19 + j]);
            }

            return tab_huffman;
        }
        else if (indice_h == DHT.pointeur[21 + nb_symbole_1][1] && DHT.pointeur[21 + nb_symbole_1][0] == indice_type)
        {
            for (int i = 0; i < 16; i++)
            {
                ajouter_chaine(&tab_huffman, DHT.pointeur[22 + nb_symbole_1 + i]);
            }

            for (int j = 0; j < nb_symbole_2; j++)
            {
                ajouter_chaine(&tab_huffman, DHT.pointeur[38 + nb_symbole_1 + j]);
            }

            return tab_huffman;
        }
        else if (indice_h == DHT.pointeur[40 + nb_symbole_1 + nb_symbole_2][1] && DHT.pointeur[40 + nb_symbole_1 + nb_symbole_2][0] == indice_type)
        {
            for (int i = 0; i < 16; i++)
            {
                ajouter_chaine(&tab_huffman, DHT.pointeur[41 + nb_symbole_1 + nb_symbole_2 + i]);
            }

            for (int j = 0; j < nb_symbole_3; j++)
            {
                ajouter_chaine(&tab_huffman, DHT.pointeur[57 + nb_symbole_1 + nb_symbole_2 + j]);
            }

            return tab_huffman;
        }
        else
        {

            for (int i = 0; i < 16; i++)
            {
                ajouter_chaine(&tab_huffman, DHT.pointeur[60 + nb_symbole_1 + nb_symbole_2 + nb_symbole_3 + i]);
            }

            for (int j = 0; j < nb_symbole_4; j++)
            {
                ajouter_chaine(&tab_huffman, DHT.pointeur[76 + nb_symbole_1 + nb_symbole_2 + nb_symbole_3 + j]);
            }

            return tab_huffman;
        }
    }

    // en cas des errures On return {0 , NULL};

    return tab_huffman;
}

/*---------------------------------------------------------------------DQT--------------------------------------------------------------------------*/

tab_chaine exctracte_table_quantification(char *composante, tab_chaine DQT, tab_chaine SOFO)
{
    tab_chaine tab_quantification = {0, NULL};

    int nb_comp = nombres_composantes(SOFO);

    // On recupere l'indice de la table de quantification pour la composante fournis en paramétre :

    tab_chaine info_comp = extracte_info_composante(composante, SOFO); // l'indice IQ est info_comp.pointeur[2]
    assert(info_comp.pointeur != NULL);                                // On continue si tout  passe bien

    if (nb_comp == 1)
    {
        // Dans le mode séquantille  DQT.pointeur[2][0]='0' // ie : precision : 8bits
        if (atoi(DQT.pointeur[2]) == atoi(info_comp.pointeur[2]))
        {
            for (int i = 0; i < 64; i++)
            {
                ajouter_chaine(&tab_quantification, DQT.pointeur[3 + i]);
            }

            liberer_tab_chaine(&info_comp);
            return tab_quantification;
        }
        else
        {
            fprintf(stderr, "Desolé : votre composante n'exite pas dans cette image jpeg \n");
        }
    }
    else
    {
        // On donc deux tables de quantification : donc nombres_com = 3 :

        char *taille_section_chaine = concatenation(DQT.pointeur[0], DQT.pointeur[1]);

        if (strcmp(taille_section_chaine, "0043") == 0)
        {
            /*---------- On a deux sections differents : --------------*/

            // en faite DQT.pointeur = "<precision><Iq>" mais en encodeur baselie precision=0 (ie 8 bits).

            if (atoi(DQT.pointeur[2]) == atoi(info_comp.pointeur[2]))
            {
                for (int i = 0; i < 64; i++)
                {
                    ajouter_chaine(&tab_quantification, DQT.pointeur[3 + i]);
                }

                liberer_tab_chaine(&info_comp);
                free(taille_section_chaine);
                return tab_quantification;
            }
            else if (atoi(DQT.pointeur[69]) == atoi(info_comp.pointeur[2]))
            {
                for (int i = 0; i < 64; i++)
                {
                    ajouter_chaine(&tab_quantification, DQT.pointeur[70 + i]);
                }

                liberer_tab_chaine(&info_comp);
                free(taille_section_chaine);
                return tab_quantification;
            }
            else
            {
                fprintf(stderr, "Desolé : votre composante n'exite pas dans cette image jpeg \n");
            }
        }
        else
        {
            /*------ On a deux tables de quantification dans une seulle section -------*/
            if (atoi(DQT.pointeur[2]) == atoi(info_comp.pointeur[2]))
            {
                for (int i = 0; i < 64; i++)
                {
                    ajouter_chaine(&tab_quantification, DQT.pointeur[3 + i]);
                }

                liberer_tab_chaine(&info_comp);
                free(taille_section_chaine);
                return tab_quantification;
            }
            else if (atoi(DQT.pointeur[67]) == atoi(info_comp.pointeur[2]))
            {
                for (int i = 0; i < 64; i++)
                {
                    ajouter_chaine(&tab_quantification, DQT.pointeur[68 + i]);
                }

                liberer_tab_chaine(&info_comp);
                free(taille_section_chaine);
                return tab_quantification;
            }
            else
            {
                fprintf(stderr, "Desolé : votre composante n'exite pas dans cette image jpeg \n");
            }
        }

        free(taille_section_chaine);
    }

    // On libere l'espace memeoire :
    liberer_tab_chaine(&info_comp);

    // En  cas d'errure  d'Usage On return {O,NULLL}
    return tab_quantification;
}

/*-------------------------------------- Extracte l'ordere de comp dans le flux --------------------------------------*/

tab_chaine order_appartion_comp(tab_chaine SOFO, tab_chaine SOS)
{
    // On recupere les identifients de composantes
    tab_chaine identifaint_Y = extracte_info_composante("Y", SOFO);
    tab_chaine identifaint_Cb = extracte_info_composante("Cb", SOFO);

    tab_chaine ordere_app = {0, NULL};

    if (strcmp(SOS.pointeur[3], identifaint_Y.pointeur[0]) == 0)
    {
        ajouter_chaine(&ordere_app, "Y");

        if (strcmp(SOS.pointeur[5], identifaint_Cb.pointeur[0]) == 0)
        {
            ajouter_chaine(&ordere_app, "Cb");
            ajouter_chaine(&ordere_app, "Cr");

            liberer_tab_chaine(&identifaint_Y);
            liberer_tab_chaine(&identifaint_Cb);

            return ordere_app;
        }
        else
        {
            ajouter_chaine(&ordere_app, "Cr");
            ajouter_chaine(&ordere_app, "Cb");

            liberer_tab_chaine(&identifaint_Y);
            liberer_tab_chaine(&identifaint_Cb);

            return ordere_app;
        }
    }
    else if (strcmp(SOS.pointeur[3], identifaint_Cb.pointeur[0]) == 0)
    {
        ajouter_chaine(&ordere_app, "Cb");

        if (strcmp(SOS.pointeur[5], identifaint_Y.pointeur[0]) == 0)
        {
            ajouter_chaine(&ordere_app, "Y");
            ajouter_chaine(&ordere_app, "Cr");

            liberer_tab_chaine(&identifaint_Y);
            liberer_tab_chaine(&identifaint_Cb);

            return ordere_app;
        }
        else
        {
            ajouter_chaine(&ordere_app, "Cr");
            ajouter_chaine(&ordere_app, "Y");

            liberer_tab_chaine(&identifaint_Y);
            liberer_tab_chaine(&identifaint_Cb);

            return ordere_app;
        }
    }
    else
    {
        ajouter_chaine(&ordere_app, "Cr");

        if (strcmp(SOS.pointeur[5], identifaint_Y.pointeur[0]) == 0)
        {
            ajouter_chaine(&ordere_app, "Y");
            ajouter_chaine(&ordere_app, "Cb");

            liberer_tab_chaine(&identifaint_Y);
            liberer_tab_chaine(&identifaint_Cb);

            return ordere_app;
        }
        else
        {
            ajouter_chaine(&ordere_app, "Cb");
            ajouter_chaine(&ordere_app, "Y");

            liberer_tab_chaine(&identifaint_Y);
            liberer_tab_chaine(&identifaint_Cb);

            return ordere_app;
        }
    }
}

/*------------------------------------- Nombre de bloc_8_fois_8 d'une comp dans une MCU ---------------------------*/

int nb_appration_bloc_8_fois_8_dans_mcu(char *composante, tab_chaine SOFO)
{
    /*
    cette fonction prend a l'entree une compossnate et reetun le nb_bloc 8x8
    de ctte composannte daans une MCU
    */

    tab_chaine facteur_echan = extracte_info_composante(composante, SOFO);

    if (strcmp(facteur_echan.pointeur[1], "21") == 0 || strcmp(facteur_echan.pointeur[1], "12") == 0)
    {
        liberer_tab_chaine(&facteur_echan);
        return 2;
    }
    else if (strcmp(facteur_echan.pointeur[1], "22") == 0)
    {
        liberer_tab_chaine(&facteur_echan);
        return 4;
    }
    else
    {
        liberer_tab_chaine(&facteur_echan);
        return 1;
    }
}

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE III DU MODULE : Des fonctions supplémentaires .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
char *concatenation(char *chaine1, char *chaine2)
{
    /*return la concatenation de deux chaine : chaine1chaine2*/

    // On alloue le memoire pour res :
    char *res = malloc(sizeof(char) * (strlen(chaine1) + strlen(chaine2) + 1));
    strcpy(res, chaine1);
    strcat(res, chaine2);

    return res;
}
