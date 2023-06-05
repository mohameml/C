#include <stdio.h>

int main(void)
{
    int age = 0 ;

    printf("saisie votre age svp : ");
    scanf("%d",&age);

    if(age>=1 && age<=12)
    {
        printf("votre age entre 1 et 12 \n");
    }
    else if(age>=12 && age<=20)
    {
        printf(" votre age entre 12 et 20 ans \n");

    }
    else
    {
        printf("votre age est superieure a 20 ans \n");
    }


    return 0 ;
}