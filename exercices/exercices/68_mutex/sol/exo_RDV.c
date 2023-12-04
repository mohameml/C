#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define N 10 

pthread_mutex_t mutex ;
pthread_cond_t cond ;


/**
 
- Ecrire un moniteur qui bloque tous
    les threads tant que N threads ne sont pas arriv´es
    en impl´ementant la fonction suivante.
    void barriere();
  
*/

int n  , m = 0 ;


void* routine()
{
    pthread_mutex_lock(&mutex);

    while(n < N)
    {
        printf("je suis le Thread numéro %d : je suis  bloquée mnt  \n", n);
        n++;
        if(n==N)
        {
            pthread_cond_broadcast(&cond);
            
        }
        else 
        {
                pthread_cond_wait(&cond , &mutex);
                
        }


        printf("je suis le Thread numéro %d : je suis  libere mnt  \n", m);
        m++;
    }


    pthread_mutex_unlock(&mutex);

    return NULL ; 
}

int compteur =0 ;


void*  routine2()
{
    pthread_mutex_lock(&mutex);


    if(compteur < N-1)
    {
        printf("je suis le Thread numéro %d : je suis  bloquée mnt  \n", compteur);

        compteur++;
        pthread_cond_wait(&cond , &mutex);
    }


    
    pthread_cond_signal(&cond);
    
    printf("nous sommes liberes mnt \n");
    pthread_mutex_unlock(&mutex);


    return NULL ;
}








int main(void)
{

    pthread_mutex_init(&mutex , NULL);
    pthread_cond_init(&cond , NULL);


    pthread_t tab[10];
    
    for(int i =0 ; i< 10 ; i++)
    {
        pthread_create(&tab[i], NULL , &routine2 , NULL);
    }

    for(int i =0 ; i< 10 ; i++)
    {
        pthread_join(tab[i] , NULL);
    }


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0 ;
}