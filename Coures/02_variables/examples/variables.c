#include <stdio.h>
int main(void)
{
    // ceci est un commentaire sur une seule lignes 
    /*
    ceci est un commentaire sur plusieres lignes 

    
    */

   // déclaration et affectations des variables 

   int  nb_1 ;
   nb_1 = 12 ;
   
   int nb_2 = 14 ; 
   float prix = 123.25 ;
   // la pertie entiere d'un float 
   int nb_3 = (int)prix ;
   

   // affichages des varaibles 
   printf("le nb_1 est %d.\n",nb_1);
   printf("le nb_1 ou le nb_2 est %d ou %d . \n",nb_1, nb_2);
   printf("le partie éntire de prix %.2f est %d. \n",prix,nb_3);

   // le mots clés const
   const float  PI =3.14 ;
   printf("PI = %.2f.\n",PI);

}