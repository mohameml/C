#include <stdio.h>
#include <stdlib.h>


// L'objectif de ce chapitre de comprend commme lire et ercrire dans un fichier 
int main(void)
{
    FILE *fichier =fopen("info.txt","r");
    // la fonction fgetc : lire un seul caracter 
    
    printf("--------la fonction fgetc------------------\n");    
    int c = 0;
    // c=fgetc(fichier);

    // printf("%c\n",c);

    // printf("----------------lire un fichier a partir de fegtc-------------------\n");
    // int lettre=0 ;
    // while(1)
    // {
    //     lettre=fgetc(fichier);
    //     if(feof(fichier))
    //        break;
        
    //     printf("%c",lettre);

    // }
    // printf("\n");

    // la fonction fgets : lire le fichier ligne par ligne 
    printf("---------------fonction fgets--------------------------\n");

    char chaine[256];

    fgets(chaine,255,fichier);

    printf("%s\n",chaine);




    return 0 ;
}