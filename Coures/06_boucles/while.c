#include <stdio.h>


/*
 le but de ce programme de calcluer les valeures de la suite : 
      U_0= 1
      U_n = 1/( U_(n-1) + 1 )
 tq L'utilisateur tape la valeur de n et le prg return U_n

*/

/*
  et voici qq valueres pour corriger vos code 
  U(100)=0.618
  U(3)=0.600
*/
int main(void)
{ 
    int n =0 ;
    printf("saisie un entier svp : ");
    scanf("%d",&n);

    float U_0 = 1;
    int i = 1;

    while (i <= n)  
    {
        U_0=1/(U_0+1);
        i++;

        
    }


    // Affichage des resltats 

    printf("La valeur de U(%d)=%.3f \n",n,U_0 );



    return 0 ;
}