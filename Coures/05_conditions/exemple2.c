#include <stdio.h>

int main(void)
{
    int age = 0;
    printf("saisie votre age svp : ");
    scanf("%d",&age);

    switch(age)
    {
        case 0 :
            printf(" votre age est 0 c'est bizare\n");
            break;
        
        case 15:
           printf("votre age est 15 \n");
           break;

        default :
           printf("bah oui votre age ni 0 ni 15 \n");
           break;
        
    }
}