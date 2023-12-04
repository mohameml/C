#include <stdio.h>
#include <pthread.h>

/*
-------------------- Simuloation des transactions sur un compte banacaire en Multi-threading -----------------------------
    -----> 1 Threads : dépose 100 
    -----> 3 Threads : rétire 50 , 30 , 20    

*/

int solde = 0 ;
pthread_mutex_t mutex ;
pthread_cond_t cond ;

void* deposer(void* arg)
{
    int montant =*((int*)arg);
    pthread_mutex_lock(&mutex);
    solde+=montant;
    printf("Dépot de %d euros -----> Solde = %d \n", montant , solde);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL ;
}


void* rétirer(void* arg)
{   
    int montant = *((int*)arg);
    pthread_mutex_lock(&mutex);

    while(solde < montant)
    {
        printf("votre solde ---> %d et montant = %d , insuffisant\n" , solde ,montant);
        pthread_cond_wait(&cond , &mutex);
    }

    solde-=montant;
    printf("Rétire d'un montant %d euros -----> Solde = %d \n", montant , solde);
    
    pthread_mutex_unlock(&mutex);
}


int main(void)
{
    /*------ initialisation de cond && mutex ----------*/
    pthread_mutex_init(&mutex , NULL);
    pthread_cond_init(&cond , NULL);


    const int n = 4;

    /*------- montants -----------*/
    int montants[] = {50 , 30 , 20 , 100};
    /*------ déclaration des threads : -----------*/
    pthread_t th[n];


    /*------- Inisialisation des threads --------------*/
    for(int i = 0 ;  i < n ; i++ )
    {
        if(i==n-1)
        {
            if(pthread_create(&th[i] , NULL , &deposer,(void*)&montants[i])!=0)
            {
                printf("Faild to create thread %d \n", i);
                return 1 ;
            }
        }
        else
        {
            if(pthread_create(&th[i] , NULL , &rétirer,(void*)&montants[i])!=0)
            {
                printf("Faild to create thread %d \n", i);
                return 1 ;
            }
        }

    }


    for(int j=0 ; j< n ; j++)
    {
        if(pthread_join(th[j] , NULL)!=0)
        {
            printf("Faild to join Threadv %d \n", j);
            return 2 ;
        }
    }



    /*---------- libération des ressources -------------*/
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0 ;

}



