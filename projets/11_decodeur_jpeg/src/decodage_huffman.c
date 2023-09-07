
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "../include/tab_chaine.h"
#include "../include/bloc_8_fois_8.h"
#include "../include/lecture_en_tete.h"

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE IV DU MODULE : Des fonctions supplémentaires .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

uint8_t convert_nibble_to_uint8_t(char lettre)
{
    /*fonction qui prend une lettre qui représente un symbole hexadecimal et le cconvert en uint8_t */

    if (lettre >= 'a' && lettre <= 'f')
    {
        return lettre - 'a' + 10;
    }
    else
    {
        return lettre - '0';
    }
}

uint16_t convert_octet_to_uint16_t(char *octet)
{
    // Une fonction qui convertit un octet écrit en chaîne de caractères vers un uin16_t

    if (strlen(octet) < 2)
    {
        // Vérifie que la chaîne contient exactement deux caractères

        printf("Erreur : La chaîne doit contenir exactement deux caractères.\n");
        exit(1);
    }

    char *ptr = NULL;

    uint16_t nombre = (uint16_t)strtol(octet, &ptr, 16);

    if (*ptr != '\0')
    {
        // Vérifie si la conversion a échoué
        printf("Erreur : Conversion invalide.\n");
        exit(1); // Quitte le programme en cas d'erreur
    }

    return nombre;
}

uint8_t convert_octet_to_uint8_t(char *octet)
{
    // Une fonction qui convertit un octet écrit en chaîne de caractères vers un uint8_t

    if (strlen(octet) < 2)
    {
        // Vérifie que la chaîne contient exactement deux caractères

        printf("Erreur : La chaîne doit contenir exactement deux caractères.\n");
        exit(1);
    }

    char *ptr = NULL;

    uint8_t nombre = (uint8_t)strtol(octet, &ptr, 16);

    if (*ptr != '\0')
    {
        // Vérifie si la conversion a échoué
        printf("Erreur : Conversion invalide.\n");
        exit(1); // Quitte le programme en cas d'erreur
    }

    return nombre;
}

uint16_t convert_bin_to_uint16_t(char *octet)
{
    // une fonction qui converti des bin ecrite en chaine de caracters vers un uint8_t

    char *ptr = NULL; // Ou sera stockee le peremie Octet non convertit par strtol

    uint16_t nombre = (uint16_t)strtol(octet, &ptr, 2);

    return nombre;
}

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE I DU MODULE : Decodage des tables Huffmman  .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* pour la somme binnaire que l'on a dèjà fait sur papier en cour d'architecture */
int sommbin(int a, int b)
{
    /* on initialise les composantes binaires ai represente le but i  de  a et le même pour bi et les autres */
    int ai;
    int bi;
    int sommei;
    int somme = 0b00000000;
    /* ci c'est la retenue entrante*/
    int ci = 0b00000000;
    /* on met 16 car la proffondeur maximum de l'arbre d'Huffman est 16 */
    for (int i = 0; i < 16; i++)
    {
        /* pour selectioner le bit de poids faible*/
        ai = (a >> i) & 1;

        bi = (b >> i) & 1;

        sommei = (ai ^ bi ^ ci);
        /* on met le bon bit de somme à la bonne position i*/
        somme |= (sommei << i);
        /* maintenat ci est la retenue sortante*/
        ci = (ai & bi) | (ai & ci) | (bi & ci);
    }
    return somme;
}

/* code_bin donne le code binaire d'un entier fourni en paramétre, sur la taille (nombre de bits) voulue */

void code_bin(int val, int taille, char **tab)
{
    (*tab)[taille] = '\0';

    /* on initialise la taille voulue par des zéros */
    for (int i = 0; i < taille; i++)
    {

        (*tab)[i] = '0';
    }

    /* on rempli les bits dans tab en utilisant la méthode connu pour le codage en binnaire (les restes de divisions  par 2)*/
    while ((val > 1) && (taille != 0))
    {

        if (val % 2 == 0)
        {
            (*tab)[taille - 1] = '0';
        }
        else if (val % 2 == 1)
        {
            (*tab)[taille - 1] = '1';
        }

        taille -= 1;
        val = (val - val % 2) / 2;
    }

    /* si la taille n'est pas rempli alors val <= 1, puis on insére val à sa position */
    if (taille != 0)
    {
        if (val == 1)
        {
            (*tab)[taille - 1] = '1';
        }
        else
        {
            (*tab)[taille - 1] = '0';
        }
    }
}

tab_chaine decodage_tab_huffman(tab_chaine tab_huffman)
{
    /*
    ENTREE : Table de Huffman extracte a partir de l'entete_jpeg
    SORTIE : Table de Huffman decode tq :
      -----> 1ere elem : Nombres_des_symboles dans tab Huffman note n .
      -----> [2 eme elem : n eme elme ] : les codes de Huffman .
      -----> [ n eme elem : fin ] : les symboles  triées par l'ordre des codes.

    */

    // on definit le tab_chaine :Table de Huffman decode

    tab_chaine tableau = {0, NULL};

    // On recupere le nombre des symobles
    int nombre_symoble = 0;

    for (int i = 0; i < 16; i++)
    {
        nombre_symoble += convert_octet_to_uint8_t(tab_huffman.pointeur[i]);
    }

    // On ajoute le nb_symbole au debut de tab_chaine :

    char chaine_nb_symbole[3];

    sprintf(chaine_nb_symbole, "%d", nombre_symoble);

    ajouter_chaine(&tableau, chaine_nb_symbole);

    // convertit le 16 premoiers elemnets en unit8_t :

    int *tab = malloc(sizeof(int) * 17);

    tab[16] = '\0';
    for (int j = 0; j < 16; j++)
    {
        tab[j] = convert_octet_to_uint8_t(tab_huffman.pointeur[j]);
    }

    int code = 0b0;

    for (int i = 0; i < 16; i++)
    {

        if (tab[i] == 0)
        {
            code = code << 1;
        }

        else if (tab[i] != 0)
        {

            for (int j = 0; j < tab[i]; j++)
            {
                char *tabi = malloc(sizeof(char) * (i + 2));
                code_bin(code, i + 1, &tabi);
                ajouter_chaine(&tableau, tabi);
                free(tabi);

                code = sommbin(code, 0b1);
            }
            code = code << 1;
        }
    }

    for (int j = 0; j < tab_huffman.taille - 16; j++)
    {
        ajouter_chaine(&tableau, tab_huffman.pointeur[16 + j]);
    }

    free(tab);

    return tableau;
}

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE II DU MODULE : Transformation de l'image en binnaire  .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

char *transformatin_image_en_binnaire(tab_chaine image)
{
    /* ctte fonctio sert a transformer les donnes brutes en biniares : en utilisant la fonction code_bin*/

    int taille = image.taille;

    char *image_bin = malloc(sizeof(char) * (8 * taille + 1));

    assert(image_bin != NULL);

    image_bin[8 * taille] = '\0';

    int compteur = 0;

    for (int i = 0; i < taille; i++)
    {

        char *tabi = malloc(sizeof(char) * 9);

        uint8_t nombre = convert_octet_to_uint8_t(image.pointeur[i]);

        code_bin(nombre, 8, &tabi);

        for (int j = 0; j < 8; j++)
        {
            image_bin[compteur + j] = tabi[j];
        }
        compteur += 8;

        free(tabi);
    }

    return image_bin;
}

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------
                           PARTIE III DU MODULE : Decodage des coefficients DC et AC   .
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

void avance_chaine(char **chaine, char elem)
{
    /* ajouter le bit suivant a la chaine pour detceter un code Huffman */
    size_t taille = strlen(*chaine);
    *chaine = realloc(*chaine, (taille + 2) * sizeof(char));
    (*chaine)[strlen(*chaine) + 1] = '\0';
    (*chaine)[strlen(*chaine)] = elem;
}

int valide_magnitude(char *chaine, tab_chaine tab_huffman)
{
    /* cette fonction sert a valider si le code obtenu est dans la tab de huffman ou non */
    int nombre_de_code = atoi(tab_huffman.pointeur[0]);

    for (int j = 1; j < nombre_de_code + 1; j++)
    {
        if (strcmp(chaine, tab_huffman.pointeur[j]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int indice_magnitude(char *chaine, tab_chaine tab_huffman)
{
    /* cette fonction return : l'inidce de code de Huffmaa daans la tab_huffman */
    int nombre_de_code = atoi(tab_huffman.pointeur[0]);

    for (int j = 1; j < nombre_de_code + 1; j++)
    {
        if (strcmp(chaine, tab_huffman.pointeur[j]) == 0)
        {
            return j;
        }
    }

    return -1; // en cas d'erreure d'Usage
}

void bar(char **chaine)
{
    /* cette ffonction sert a calculer le complemnatire d'un code binaire
     par exemple : bar(&"1000")=0111

    */
    int taille = strlen(*chaine);

    for (int i = 0; i < taille; i++)
    {
        if ((*chaine)[i] == '0')
        {
            (*chaine)[i] = '1';
        }
        else
        {
            (*chaine)[i] = '0';
        }
    }
}

int decode_val_exacte(char **chaine)
{
    /* cette fonction return excatemeent l'indice de nombre dans la classe magntiude */
    if ((*chaine)[0] == '1')
    {
        return convert_bin_to_uint16_t(*chaine);
    }
    else
    {
        bar(chaine);
        return -convert_bin_to_uint16_t(*chaine);
    }
}

void decodage_RLE(char *image_bin_AC, tab_chaine tab_huffman_AC, int tableau_des_val_AC[], int *indice, int *compteur)
{

    /* cette fonction sert a decoder les coefficents AC : pour un bloc 8x8*/

    /* on recupere tout d'abord le code de Huffman de symbole  */

    char *code_coef_RLE = malloc(sizeof(char) * 2);
    code_coef_RLE[1] = '\0';
    code_coef_RLE[0] = image_bin_AC[*compteur];
    (*compteur)++;

    while (valide_magnitude(code_coef_RLE, tab_huffman_AC) != 1)
    {
        /* on avance le chaine vers le bit suivant jusqu'a detecter un code de Huffmman */
        avance_chaine(&code_coef_RLE, image_bin_AC[*compteur]);
        (*compteur)++;
    }

    // on recupere l'indice de la code de symbole  :

    int indice_code_coef_RLE = indice_magnitude(code_coef_RLE, tab_huffman_AC);

    assert(indice_code_coef_RLE != -1);

    char *symbole = malloc(sizeof(char) * 3);
    symbole[2] = '\0';

    int nb_symble = atoi(tab_huffman_AC.pointeur[0]);

    // recupere le symbole

    strcpy(symbole, tab_huffman_AC.pointeur[indice_code_coef_RLE + nb_symble]);

    if (strcmp(symbole, "00") == 0)
    {
        /* si on detcete un symbbole 00 donc tout ce qui reste est 0 */
        int position = *indice;

        for (int j = position; j < 64; j++)
        {
            tableau_des_val_AC[j] = 0;
        }

        *indice = 64;
    }
    else if (strcmp(symbole, "f0") == 0)
    {
        /* si on detcete le symbole "f0" : donc 16 elem egale a 0 :*/
        for (int j = 0; j < 16; j++)
        {
            tableau_des_val_AC[(*indice) + j] = 0;
        }

        (*indice) += 16;
    }
    else
    {
        //  0x?0 : symbole invalide (interdit!)
        assert(symbole[1] != 0);

        //  (pour AC, la classe max est 10 et la magnitude 0 n'est jamais utilisée)

        // la classe magntiude en int
        int classe_magn_int = convert_nibble_to_uint8_t(symbole[1]);

        // le code bin de la valeur dans la classe de magnitude correspondante
        char *val_bin = malloc(sizeof(char) * (classe_magn_int + 1));

        // valbin qui contient les m bits suivant le symbole

        val_bin[classe_magn_int] = '\0';

        for (int j = 0; j < classe_magn_int; j++)
        {
            val_bin[j] = image_bin_AC[*compteur + j];
        }

        // pour avancer le compteur par  taille de la classe de magntiude  (le compteur de lecture de image_bin)
        (*compteur) += classe_magn_int;

        int val_fin = decode_val_exacte(&val_bin);

        /* On recupere le nombre de zero :*/
        int nbr_zero = convert_nibble_to_uint8_t(symbole[0]);
        for (int j = 0; j < nbr_zero; j++)
        {
            tableau_des_val_AC[*indice + j] = 0;
        }

        (*indice) += nbr_zero;

        tableau_des_val_AC[*indice] = val_fin;
        (*indice)++;

        free(val_bin);
    }

    free(symbole);
    free(code_coef_RLE);
}

void decodage_image_Huffman(char *image_en_bin, tab_chaine tab_huffman_DC, tab_chaine tab_huffman_AC, int image_decode[], int *DC_precedent, int *compteur)
{
    /*
    ENTREE : image_en_bin , tab de HUffman_AC  qui contient : le decodage des symboles de Huffman
    SORTIE : un bloc 8x8 decode .
   */

    /*---------------------------------------- Traitement_DC : --------------------------------------*/

    // pour la position de l'ecriture dans image_decode
    int position = 0;

    // classe_mag : représente le code de la classe magnitude

    char *classe_mag = malloc(sizeof(char) * 2);
    // on l'initialise avec la 1ere char  en image en bin

    classe_mag[0] = image_en_bin[*compteur];
    classe_mag[1] = '\0';
    (*compteur)++;

    // pour  la position de lecture a partir  image_en_bin
    //  int compteur = 1 pour le parcour (detection du code de la classe magnitude )

    while (valide_magnitude(classe_mag, tab_huffman_DC) != 1)
    {
        avance_chaine(&classe_mag, image_en_bin[*compteur]);
        (*compteur)++;
    }

    // on recupere l'indice de la classe de magnitude :

    int indice = indice_magnitude(classe_mag, tab_huffman_DC);

    assert(indice != -1);

    char *magnitude = malloc(sizeof(char) * 3);
    magnitude[2] = '\0';

    int nb_symble = atoi(tab_huffman_DC.pointeur[0]);

    // recupere la classe de magnitude

    strcpy(magnitude, tab_huffman_DC.pointeur[indice + nb_symble]);

    // le nombre
    int magnitude_int = convert_octet_to_uint8_t(magnitude);

    /*------------recuperation des m bits de la val apres le code de la classe de magnitude-------------*/

    // le code bin de la valeur dans la classe de magnitude correspondante
    char *val_bin = malloc(sizeof(char) * (magnitude_int + 1));

    val_bin[magnitude_int] = '\0';

    for (int j = 0; j < magnitude_int; j++)
    {
        val_bin[j] = image_en_bin[*compteur + j];
    }

    int val_fin = decode_val_exacte(&val_bin);

    image_decode[0] = val_fin + *DC_precedent;
    position++;

    // le compteur pour la po
    (*compteur) += magnitude_int;
    *DC_precedent = image_decode[0];

    /*------------------------------------------- ajoute de AC : ---------------------------------------------*/

    while (position < 64)
    {
        decodage_RLE(image_en_bin, tab_huffman_AC, image_decode, &position, compteur);
    }

    free(val_bin);
    free(classe_mag);
    free(magnitude);
}

/*----------------------------------------- Decodage d'une MCU ---------------------------------------*/

void decodage_Huffman_mcu(mcu_vect *mcu_flux, char *image_en_bin, tab_chaine tab_Huffman_Y_DC, tab_chaine tab_Huffman_Y_AC, tab_chaine tab_Huffman_Cb_Cr_DC, tab_chaine tab_Huffman_Cb_Cr_AC, tab_chaine SOS, tab_chaine SOFO, int *compteur, int *DC_precedent_Y, int *DC_precedent_Cb, int *DC_precedent_Cr)
{
    /*
    cette fonction sert a decoder une MCU et le stocke dans une strucure mcu_vect :

    */
    // On recuoere l'ordere d'appartion de comp dans le flux
    tab_chaine ordere_app = order_appartion_comp(SOFO, SOS);

    // On recupere le nb d'apartion de bloc 8x8 dans une MCU :

    int nb_bloc_Y = nb_appration_bloc_8_fois_8_dans_mcu("Y", SOFO);
    int nb_bloc_Cb = nb_appration_bloc_8_fois_8_dans_mcu("Cb", SOFO);
    int nb_bloc_Cr = nb_appration_bloc_8_fois_8_dans_mcu("Cr", SOFO);

    if (strcmp(ordere_app.pointeur[0], "Y") == 0)
    {
        /* si Y est le premiere dans le flux : */
        for (int i = 0; i < nb_bloc_Y; i++)
        {
            /* on decode bloc 8x8 par bloc 8x8 on l'insere dans une liste chainee */

            bloc_8_fois_8 bloc;
            decodage_image_Huffman(image_en_bin, tab_Huffman_Y_DC, tab_Huffman_Y_AC, bloc.data_vect_64, DC_precedent_Y, compteur);
            inserer_mcu(&mcu_flux->data_vect_Y, bloc);
        }

        if (strcmp(ordere_app.pointeur[1], "Cb") == 0)
        {
            for (int i = 0; i < nb_bloc_Cb; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cb, compteur);
                inserer_mcu(&mcu_flux->data_vect_Cb, bloc);
            }

            for (int i = 0; i < nb_bloc_Cr; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cr, compteur);
                inserer_mcu(&mcu_flux->data_vect_Cr, bloc);
            }
        }
        else
        {
            for (int i = 0; i < nb_bloc_Cr; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cr, compteur);
                inserer_mcu(&(mcu_flux->data_vect_Cr), bloc);
            }

            for (int i = 0; i < nb_bloc_Cb; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cb, compteur);
                inserer_mcu(&(mcu_flux->data_vect_Cb), bloc);
            }
        }
    }
    else if (strcmp(ordere_app.pointeur[0], "Cb") == 0)
    {
        /* si Cb est le 1ere dans le flux :*/
        for (int i = 0; i < nb_bloc_Cb; i++)
        {
            bloc_8_fois_8 bloc;
            decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cb, compteur);
            inserer_mcu(&(mcu_flux->data_vect_Cb), bloc);
        }

        if (strcmp(ordere_app.pointeur[1], "Y") == 0)
        {
            for (int i = 0; i < nb_bloc_Y; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Y_DC, tab_Huffman_Y_AC, bloc.data_vect_64, DC_precedent_Y, compteur);
                inserer_mcu(&(mcu_flux->data_vect_Y), bloc);
            }

            for (int i = 0; i < nb_bloc_Cr; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cr, compteur);
                inserer_mcu(&mcu_flux->data_vect_Cr, bloc);
            }
        }
        else
        {
            for (int i = 0; i < nb_bloc_Cr; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cr, compteur);
                inserer_mcu(&mcu_flux->data_vect_Cr, bloc);
            }

            for (int i = 0; i < nb_bloc_Y; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Y_DC, tab_Huffman_Y_AC, bloc.data_vect_64, DC_precedent_Y, compteur);
                inserer_mcu(&mcu_flux->data_vect_Y, bloc);
            }
        }
    }
    else
    {
        /* si le Cr est le 1ere dans le flux : */

        for (int i = 0; i < nb_bloc_Cr; i++)
        {
            bloc_8_fois_8 bloc;
            decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cr, compteur);
            inserer_mcu(&mcu_flux->data_vect_Cr, bloc);
        }

        if (strcmp(ordere_app.pointeur[1], "Y") == 0)
        {
            for (int i = 0; i < nb_bloc_Y; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Y_DC, tab_Huffman_Y_AC, bloc.data_vect_64, DC_precedent_Y, compteur);
                inserer_mcu(&mcu_flux->data_vect_Y, bloc);
            }

            for (int i = 0; i < nb_bloc_Cb; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cb, compteur);
                inserer_mcu(&mcu_flux->data_vect_Cb, bloc);
            }
        }
        else
        {
            for (int i = 0; i < nb_bloc_Cb; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Cb_Cr_DC, tab_Huffman_Cb_Cr_AC, bloc.data_vect_64, DC_precedent_Cb, compteur);
                inserer_mcu(&mcu_flux->data_vect_Cb, bloc);
            }

            for (int i = 0; i < nb_bloc_Y; i++)
            {
                bloc_8_fois_8 bloc;
                decodage_image_Huffman(image_en_bin, tab_Huffman_Y_DC, tab_Huffman_Y_AC, bloc.data_vect_64, DC_precedent_Y, compteur);
                inserer_mcu(&mcu_flux->data_vect_Y, bloc);
            }
        }
    }

    liberer_tab_chaine(&ordere_app);
}
