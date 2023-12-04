#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

/*
---------------- Exemple sqsur l'utilisation du semaphore : --------------------
    ----> serveur : aux max 12 utilisateures a méme temps 
    ----> Exemple : on 16 utilisateures (Thread)    
*/

#define N 16

/*----- déclaration du semaphore ------*/
sem_t sem ;

void* routine(void* arg)
{
    int id = *(int*)arg ;
    
    printf("Thread %d : waiting in the login queue \n" , id);
    sem_wait(&sem); /* la fonction P du sémaphore  : s.C0-- */
    printf("Thread %d : login in the server \n" , id);
    sleep(1);
    printf("Thread %d :logout from hte server \n" , id);
    sem_post(&sem); /* la fonction V du sémaphore  : s.C0++ */


    free(arg);
    
    return NULL ;
}


int main(void)
{

    /*------ initialisation du sémaphore: -------*/
    sem_init(&sem , 0 , 12); /*0 : si on  seulle processus , 1 : valeur initiale du processus*/

    pthread_t th[N];

    for(int i=0 ; i< N ;i++)
    {
        int* ptr_id = malloc(sizeof(int));
        *ptr_id = i;
        if(pthread_create(&th[i] , NULL , &routine , ptr_id)!=0)
        {
            printf("Faild to create Thread %d \n", i);
        }
    }



    for(int i = 0  ; i < N ; i++)
    {
        if(pthread_join(th[i] , NULL)!=0)
        {
            printf("Faild to join Thread %d \n" , i);
        }
    }



    /*---- libération de sémaphores -----*/
    sem_destroy(&sem);


    return 0 ;
}


