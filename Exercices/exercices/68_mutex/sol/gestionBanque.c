#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

/*-------------------------- gestion d'un compte banquaire  --------------------------*/

int solde = 0 ;

pthread_mutex_t mutex ;
pthread_cond_t cond ;



void* deposer(void* arg)
{
    int m = *((int *)arg);

    pthread_mutex_lock(&mutex); 

    solde+=m;
    printf("depot du %d euro , votre solde mnt est : %d \n", m , solde);


    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);


    return NULL ; 
}



void* rétirer(void * arg)
{
    int m = *((int*)arg);




    pthread_mutex_lock(&mutex);

    while(m > solde)
    {
        printf("le montant a rétirer est %d , et votre solde est : %d  ---> impossible de faire un rétrait \n " , m ,solde);

        pthread_cond_wait(&cond, &mutex);
    }


    solde-=m ;
    printf("un rétrait avce sucées du m %d euro --> votre solde mnt est %d \n" , m , solde );



    pthread_mutex_unlock(&mutex);


    return NULL ;
}




int main(void)
{

    pthread_mutex_init(&mutex ,NULL);
    pthread_cond_init(&cond , NULL);

    pthread_t tab[3];
    int montant[] = {25 ,50 , 100};

    for(int i =0 ; i< 3 ; i++)
    {
        
        if(i==2)
        {
            pthread_create(&tab[i] , NULL , deposer , &montant[i] );
        }
        else
        {
            pthread_create(&tab[i] , NULL , rétirer , &montant[i]);

        }
    }


    for(int i =0 ; i< 3 ; i++)
    {
        pthread_join(tab[i] , NULL);
    }


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0  ; 
}


