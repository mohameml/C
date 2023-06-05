#include <stdio.h>

int main(void)
{
    int nb_1 = 0;
    int nb_2 = 0;
  

    printf("ceci un entier nb_1 ");
    scanf("%d",&nb_1);

    printf("ceci un nb_2 ");
    scanf("%d",&nb_2);
    int nb = nb_1 + nb_2 ;

    printf("la somme de nb_1 et nb_2 %d \n",nb);

    return 0 ;

}