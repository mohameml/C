#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
/*
- déclarer et initaliser un thread th 
- passer a th deux args : int age et char* nom 
- le thread : affiche  je suis "nom" et j'ai "age" ans .
- et return l'age .
- récupere l'age retourner par le thread et l'afficher 

*/


struct Args
{
    int age ;
    char* msg ;
};


void* routine(void* args)
{
    struct Args* args_th = (struct Args*)args ;

    int age = args_th->age ;
    char* msg = args_th->msg;


    printf("je suis %s , et j'ai  %d  ans  \n", msg , age);


    // et on return l'age 
    int* age_r = malloc(sizeof(int));
    *age_r = age ;


    return (void*)age_r ;
}



int main(void)
{
    pthread_t th ;

    struct Args  args = {22 ,"Nebil"};


    if(pthread_create(&th , NULL , &routine ,&args)!=0)
    {
        printf("Faild to create Thread \n");
        return 1 ;
    }


    int* age_r = NULL ;



    if(pthread_join(th , (void**)&age_r)!=0)
    {
        printf("Faiold to join Thread \n");
        return 2 ;
    }



    int age = *age_r ;


    printf("l'age récupérer  est %d \n" , age);

    free(age_r);    
    return 0 ;
}