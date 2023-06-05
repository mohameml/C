#include <stdio.h>
void inverser(int a , int b);
void inverser1(int *a , int *b);

int main(void)
{
   int a=1;
   int b=2;

   // sans utiliser les pointeures 


   printf("Sans utiliser les pointeures  \n");
   printf("Les valeures intiales a=%d , b=%d \n",a,b);
   inverser(a,b);
   printf ("les valeures suivantes a=%d, b=%d \n",a,b); 

   printf("-----------------------------\n");

   // en utilisant les poointeures 
   int *pt_a = &a;
   int *pt_b = &b;

   printf("En utilisant les poointeures :\n");

   printf("Les valeures intiales a=%d , b=%d \n",a,b);
   inverser1(pt_a,pt_b);
   printf ("les valeures suivantes a=%d, b=%d \n",a,b); 
   
   // pointeur de pointeur 
   int **pt_pt_a = &pt_a;

   printf("pointeur de pointeur \n");
   printf("%d\n",**pt_pt_a);

}


void inverser(int a , int b)
{
    int tmp = 0 ;
    tmp = b;
    a = b;
    b = tmp;

}


void inverser1(int *a , int *b)
{
    int tmp = 0 ;
    tmp = *a;
    *a = *b;
    *b = tmp;

}


