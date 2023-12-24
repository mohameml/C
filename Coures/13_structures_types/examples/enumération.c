#include <stdio.h>


enum Naturel {ZER0,UN , Deux, Trois , Quatre };

typedef enum joures {Lundi , Mardi, Mercreddi , Jeudi , VEndredi ,Samedi , Dimanche  } Joures ;


int main(void)
{
    enum Naturel n=ZER0;
    printf("%d\n",n);

    printf("----------------------------------\n");
    printf("UN=%d\n",UN);



    printf("----------------------------------\n");
    Joures j1=Lundi;
    printf("Lundi=%d\n",j1);


    return 0 ;
}