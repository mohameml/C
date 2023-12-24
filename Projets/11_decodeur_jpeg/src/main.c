#include <stdio.h>

#include "../include/decodeur_baseline.h"


int main(int argc, char **argv)
{
    /* -------------------------On verifie tout d'abord le bon usage de programme---------------------------- */

    if (argc != 2) 
    {
        /* 
        il faut deux argeument pour que le programme sa marche : fichier.jpeg et 1 pour gdb
        */
        fprintf(stderr, "Usage: %s fichier.jpeg \n", argv[0]);
        return EXIT_FAILURE;
    }
   
   /*----------------- On applle notre decodeur : decodeur_baseline ------------------------*/
   decodeur_baseline(argv[1]);
   

    


    return 0;
}