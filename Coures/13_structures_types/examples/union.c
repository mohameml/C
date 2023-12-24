#include <stdio.h>
#include <string.h>


union type
{
    int entier ;
    float decimal ;
    char chaine[256] ;
};

int main(void)
{
    union type t1;

    t1.entier=12;
    t1.decimal=12.23;
    strcpy(t1.chaine,"Bonjour sidi");

    printf("t1.entier=%d \n",t1.entier);
    printf("t1.decimal=%f \n",t1.decimal);
    printf("t1.decimal=%s \n",t1.chaine);



    return 0 ;
}